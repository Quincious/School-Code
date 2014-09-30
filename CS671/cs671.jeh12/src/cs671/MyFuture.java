package cs671;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

/**
 * Created by Quincious on 3/13/14.
 */
class MyFuture<T> implements Future<T>,Runnable{

    private T result;
    private boolean isDone;
    private boolean abnormalEnd;
    private boolean runnableTask;
    private Throwable error;

    private Runnable rTask;
    private Callable<T> cTask;

    private List<Callback<? super T>> whenCompleteCallbacks = new LinkedList<>();
    private List<Runnable> whenCompleteRunnables = new LinkedList<>();
    private List<MyFuture<?>> whenCompleteContinues = new LinkedList<>();

    private Object callBackBlock = new Object();
    private Object getBlock = new Object();

    /**
     * Builds a future from runnable task
     */
    public MyFuture(Runnable task){

        rTask = task;
        runnableTask = true;
        result = null;
        isDone = false;
        abnormalEnd = false;
    }

    /**
     * Builds a future from callable task
     */
    public MyFuture(Callable<T> task){

        cTask = task;
        runnableTask = false;
        result = null;
        isDone = false;
        abnormalEnd = false;
    }



    public void run(){
        try{
            if(runnableTask)
                rTask.run();
            else
                result = cTask.call();

            while(true){
            synchronized (callBackBlock){

                    if(!whenCompleteRunnables.isEmpty()){
                        whenCompleteRunnables.remove(0).run();
                        continue;
                    }

                    if (!whenCompleteCallbacks.isEmpty()){
                        whenCompleteCallbacks.remove(0).call(result);
                        continue;
                    }

                    if(!whenCompleteContinues.isEmpty()){
                        whenCompleteContinues.remove(0).run();
                        continue;
                    }

                    isDone = true;
                }

                synchronized (getBlock){
                    getBlock.notifyAll();
                }

                break;
            }

        }catch(Exception ex){
            error = ex;
            abnormalEnd = true;

            while(true){
            synchronized (callBackBlock){

                if(!whenCompleteCallbacks.isEmpty()){
                    whenCompleteCallbacks.remove(0).failure(error);
                    continue;
                }

                if(!whenCompleteContinues.isEmpty()){
                    whenCompleteContinues.remove(0).dontRun(ex);
                    continue;
                }

                isDone = true;

            }

            synchronized (getBlock){
                getBlock.notifyAll();
            }
                break;
            }

        }
    }

    /** Checks the future for completion.
     * @return true iff the underlying computation has terminated,
     * normaly or abruptly.
     */
    public boolean isDone (){
        return isDone;
    }

    /** Computation result.  This method blocks the calling thread if
     * the underlying computation has not terminated yet.
     * @return the value produced by the computation under normal
     * termination, or {@code null} if the computation terminated
     * abruptly.
     */
    public synchronized T get () throws InterruptedException {

        synchronized (getBlock){
            while(!isDone){
                getBlock.wait();
            }
            getBlock.notifyAll();
        }
        return abnormalEnd ? null : result;
    }

    /** Computation failure.  This method blocks the calling thread if
     * the underlying computation has not terminated yet.
     * @return the error or exception that caused the computation to
     * terminate abrupty, or {@code null} if the computation terminated
     * normally.  Note that {@code getFailure() == null} is true exactly
     * when a computation terminates normally, while {@code get() ==
     * null} can be true of a successful null-producing computation.
     */
    public synchronized Throwable getFailure () throws InterruptedException{

        synchronized (getBlock){
            while(!isDone){
                getBlock.wait();
            }
            getBlock.notifyAll();
        }

        return abnormalEnd ? error : null;
    }

    /** Attaches a callback.  After the underlying computation
     * terminates, the callback object's {@code call} will be invoked
     * with the result of the computation, if it terminated
     * successfully.  Upon failure of the underlying computation, the
     * callback's {@code failure} method will be invoked instead, with
     * the error or exception that caused the failure.  Only one of the
     * callback's method will be invoked.  The invocation will take
     * place <em>after</em> the computation finishes and <em>before</em>
     * {@code isDone} returns {@code true} and blocked threads are
     * released from {@code get} or {@code getFailure}, if any.
     */
    public void whenComplete (Callback<? super T> callback){

        synchronized (callBackBlock){

            if(isDone)
                if(abnormalEnd)
                    callback.failure(error);
                else
                    callback.call(result);
            else
                whenCompleteCallbacks.add(callback);
        }
    }

    /** Attaches a callback.  After the underlying computation
     * terminates successfully, the callback object's {@code run} will
     * be invoked.  No call is made if the underlying computation fails.
     * The invocation will take place <em>after</em> the computation
     * finishes and <em>before</em> {@code isDone} returns {@code true}
     * and blocked threads are released from {@code get} or {@code
     * getFailure}, if any.
     */
    public void whenComplete (Runnable callback){

        synchronized (callBackBlock){

            if(isDone)
                if(!abnormalEnd)
                    callback.run();
            else
                whenCompleteRunnables.add(callback);
        }
    }

    /** Attaches a continuation.  After the underlying computation
     * terminates successfully, the continuation object's {@code call}
     * will be invoked with the result of the computation.  No call is
     * made if the underlying computation fails.  The invocation will
     * take place <em>after</em> the computation finishes and
     * <em>before</em> {@code isDone} returns {@code true} and blocked
     * threads are released from {@code get} or {@code getFailure}, if
     * any.
     *
     * <p> If the underlyong computation fails, the continuation is not
     * executed.  The future's {@code get} method retuns {@code null}
     * and its {@code getFailure} method retuns an instance of {@code
     * NotExecutedException} with the failure of the underlying
     * computation as its cause.
     * @return a future on the seconday computation.  This future
     * completes when the secondary computation terminates or when the
     * first computation fails.
     * @see NotExecutedException
     * @see NotExecutedException#getCause
     */
    public <U> Future<U> whenComplete (Continue<? super T, ? extends U> cont){

        synchronized (callBackBlock){

            if(isDone){
                if(abnormalEnd){
                    return new FailedFuture<>(new NotExecutedException(error));
                }
                try {
                    return new CompletedFuture<>(cont.call(result));
                } catch (Exception e) {
                    return new FailedFuture<>(new NotExecutedException(e));
                }
            }

            final Continue<? super T, ? extends U> finalCont = cont;

            Callable<U> newCall = new Callable<U>() {

                public U call() throws Exception {
                    return finalCont.call(result);
                }
            };

            MyFuture<U> retVal = new MyFuture<>(newCall);
            whenCompleteContinues.add(retVal);
            return retVal;
        }
    }

    void dontRun(Throwable error){
        result = null;
        this.error = new NotExecutedException(error);
        abnormalEnd = true;

        while(true){
            synchronized (callBackBlock){

                if(!whenCompleteContinues.isEmpty()){
                    whenCompleteContinues.remove(0).dontRun(error);
                    continue;
                }

                isDone = true;

                synchronized (getBlock){
                    getBlock.notifyAll();
                }

                break;
            }
        }

    }
}
