		

package cs671;

public class HiLo<T> extends Object implements Guesser<Integer> {

	/**
	 * Class Private Variables
	 */	
	private int minimum;			//Minimum declared at beginning
	private int maximum;			//Maximum declared at beginning
	private int currentMinimum;		//Minimum for the current game
	private int currentMaximum;		//Maximum for the current game
	private int currentGuess;		//Value program will ask if answer is greater than
	private boolean isInitialized;	//Flag to track initialization
	private boolean isSolved;		//Flag to track if answer found
	private boolean questionAsked;	//Flag to track if an answer was asked

	
	/**Builds an instance of the engine for the given minimum and maximum.
	 * 
	 * @throws IllegalArgumentException if max is not greater than min
	 * @param min the lower bound of the range
	 * @param max the upper bound of the range
	 */
	public HiLo(int min, int max){
		
		if(min > max)
			throw new IllegalArgumentException(); //Max isn't larger, throw exception

		minimum = min;
		maximum = max;
		currentMinimum = 0;
		currentMaximum = 0;
		currentGuess = 0;
		isInitialized = false;
		isSolved = false;
		questionAsked = false;
	}
	
	/** Initializes HiLo.  This method must be called to
	   * initiate a problem before the rounds of questions and answers begin.
	   *
	   * @return An initialization message that can be displayed to the user
	   */
	public String initialize() {

		isInitialized = true;
		
		currentMinimum = minimum;
		currentMaximum = maximum;
		isSolved = false;
		questionAsked = false;
		currentGuess = 0;
		
		return "Pick a number between " + minimum + " and " + maximum;
	}

	/** Whether the problem has been solved.  While this method returns
	   * <code>false</code>, users should continue to call methods
	   * <code>makeQuestion</code>, <code>yes</code> and <code>no</code>.
	   * Once it returns <code>true</code>, the method
	   * <code>getSecret</code> can safely be called.
	   *
	   * @return <code>true</code> iff the problem has been solved
	   * @throws IllegalStateException if the engine has not been initialized
	   * @see #makeQuestion
	   * @see #yes
	   * @see #no
	   * @see #getSecret
	   */
	public boolean hasSolved() {
		
		if(!isInitialized)
			throw new IllegalStateException();	//Not initialized, throw exception

		if(currentMinimum == currentMaximum) 
			isSolved = true;					//only one number left therefore it is answer
		
		return isSolved;
	}

	/** The answer to the problem.  This method should be called after
	   * <code>hasSolved</code> returns <code>true</code> to retreive the
	   * solution to the problem.
	   *
	   * @return the answer to the problem, if it is known
	   * @throws IllegalStateException if the problem has not yet been solved
	   * or the guesser has not been initialized
	   * @see #hasSolved
	   */
	public Integer getSecret() {
		
		if(!isInitialized || !isSolved)
			throw new IllegalStateException();	//Not initialized or solved, throw exception		
		
		//if getting secret, game is over, uninitialize
		isInitialized = false;
		
		return currentMaximum;
	}

	/** Used to reply YES to the previous question.  Method
	   * <code>makeQuestion</code> must be called to generate a question
	   * before calling <code>yes</code> or <code>no</code>.
	   *
	   * @throws IllegalStateException if <code>makeQuestion</code> has
	   * not been called first or the guesser has not been initialized
	   * @see #makeQuestion
	   * @see #no
	   */
	public void yes() {
		
		if(!isInitialized || !questionAsked)
			throw new IllegalStateException();	//Not initialized or hasn't asked question, throw exception
		
		currentMinimum = currentGuess + 1;		
		questionAsked = false;
		
	}

	/** Used to reply NO to the previous question.  Method
	   * <code>makeQuestion</code> must be called to generate a question
	   * before calling <code>yes</code> or <code>no</code>.
	   *
	   * @throws IllegalStateException if <code>makeQuestion</code> has
	   * not been called first or the guesser has not been initialized
	   * @see #makeQuestion
	   * @see #yes
	   */
	public void no() {
		if(!isInitialized || !questionAsked)
			throw new IllegalStateException();	//Not initialized or hasn't asked question, throw exception
		
		currentMaximum = currentGuess;		
		questionAsked = false;			
		
	}

	/** Generates a new question.  The previous question must be
	   * answered (using <code>yes</code> or <code>no</code>) before a new
	   * question is generated.
	   *
	   * @return the question, as a string to be displayed to the user
	   * @throws IllegalStateException if the guesser is not initialized,
	   * the problem is already solved or the previous question has not
	   * been answered
	   * @see #initialize
	   * @see #hasSolved
	   * @see #yes
	   * @see #no
	   */
	public String makeQuestion() {
		
		if(!isInitialized || isSolved || questionAsked)	
			throw new IllegalStateException();		//Not initialized or already solved or asked question, throw exception
		
		currentGuess = ((currentMaximum - currentMinimum)/2) + currentMinimum;	
		
		questionAsked = true;
			
		return "Is your number larger than " + currentGuess + "? ";
	}

	/** Indicates progress towards solving the problem.  After
	   * initialization, the value returned is 0 (unless the problem is
	   * immediately solved, in which case it is 1).  It always increases
	   * as the guessing process progresses.  It is exactly 1 after the
	   * problem is solved.
	   *
	   * @return a value between 0 and 1 that is a measure of how much
	   * progress has been made towards solving the problem
	   * @throws IllegalStateException if the engine has not been initialized
	   */
	public double progress() {
		
		if(!isInitialized)
			throw new IllegalStateException();		//Not initialized, throw exception
		
		
		if(hasSolved())
			return 1.0;
		
		double startDifference = (double)maximum - (double)minimum;
		double currentDifference = (double)currentMaximum - (double)currentMinimum;		
		
		return (1.0 - (currentDifference/startDifference));
	}

}
