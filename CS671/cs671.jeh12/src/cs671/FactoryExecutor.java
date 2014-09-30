package cs671;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * Created by Quincious on 3/12/14.
 */
public final class FactoryExecutor implements Executor {

    public static interface ThreadFactory{

        Thread getThread(Runnable behavior);
    }


    ThreadFactory myFactory;

    /**
     * creates a new executor.
     * When tasks are submitted, worker threads will be created from the given factory.
     */
    public FactoryExecutor(FactoryExecutor.ThreadFactory factory){

        this.myFactory = factory;

    }

    /** Submits a callable task for execution.
     * @return a future with the given task as its underlying computation
     */
    public <T> Future<T> execute(Callable<T> task) {

        MyFuture<T> retVal = new MyFuture<>(task);
        myFactory.getThread(retVal).start();

        return retVal;
    }

    /** Submits a runnable task for execution.  Note that the result
     * returned by {@code Future.get} will be {@code null}, whether the
     * task terminates normally or abruptly.
     * @return a future with the given task as its underlying computation
     * @see Future#get
     */
    public <T> Future<T> execute(Runnable task) {

        MyFuture<T> retVal = new MyFuture<>(task);
        myFactory.getThread(retVal).start();

        return retVal;
    }

    /** Submits a callable task for execution, alongside a callback.
     * After the task terminates, the callback's {@code call} method
     * will be invoked with the value produced by the task, if the task
     * was successful.  If the task fails abruptly, the callback's
     * {@code failure} method will be called instead, with the cause of
     * the failure.
     */
    public <T> void execute(Callable<T> task, Callback<? super T> callback) {

        final Callable<T> t = task;
        final  Callback<? super T> c = callback;
        Runnable r = new Runnable() {

            public void run() {
                try{
                    c.call( t.call());
                }catch (Exception ex){
                    c.failure(ex);
                }
            }
        };

        myFactory.getThread(r).start();
    }

    /** Submits a runnable task for execution, alongside a callback.
     * After the task terminates, the callback's {@code call} method
     * will be invoked with {@code null}, if the task
     * was successful.  If the task fails abruptly, the callback's
     * {@code failure} method will be called instead, with the cause of
     * the failure.
     */
    public <T> void execute(Runnable task, Callback<T> callback) {

        final Runnable t = task;
        final  Callback<? super T> c = callback;
        Runnable r = new Runnable() {

            public void run() {
                try{
                    t.run();
                    c.call(null);
                }catch (Exception ex){
                    c.failure(ex);
                }
            }
        };

        myFactory.getThread(r).start();

    }
}
