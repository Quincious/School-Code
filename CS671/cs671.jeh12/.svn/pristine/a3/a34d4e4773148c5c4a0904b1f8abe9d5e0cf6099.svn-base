package cs671;

import java.util.*;

public class Liar<T> implements Guesser<Liar.Secret<T>> {

	/**
	 * Class Private Variables
	 */	
	private boolean isInitialized;	//Flag to track initialization
	private boolean isSolved;		//Flag to track if answer found
	private boolean questionAsked;	//Flag to track if an answer was asked
	private int numOfQuestions;		//number of questions asked
	private ArrayList<T> allCandidates;//Full list of candidates.
	
	
	/**
	 * Class Public Variables 
	 */	
	public final int maxLies;		//Maximum number of times a use can lie.
	public final String name;		//How secrets objects are referred
	
	
	/**
	 * These Maps are used for the Liar algorithm.
	 * Other variables are used to assist with algorithm
	 */
	private Map<Integer,ArrayList<T>> upperPile;//upper pile of 
	private Map<Integer,ArrayList<T>> lowerPile;
	private double totalLiesPossible;		//used to calculate progress
	
	public static class Secret<E> extends Object{
		
		/**
		 * Class Private Variables
		 */
		private int numberOfLies;//number of user lies
		private E userSecret;//users secret		
		
		/**
		 * Constructor
		 * 
		 * The type of secrets produced by this guesser. 
		 * Secrets are simply a pair: secret object and number of times the user lied.
		 * 
		 * This constructor package-private by default
		 * 
		 * @param numOfLies number of lies told by user
		 * @param userSecret user secret
		 */
		Secret(int numOfLies, E userSecret){
			this.numberOfLies = numOfLies;
			this.userSecret = userSecret;
		}
		
		/**
		 * The secret that was discovered, of type T
		 * 
		 * @return	user's secret
		 */
		public E getSecret(){
			return userSecret;
		}
		
		/**
		 * The number of times the user lied during the discovery process
		 * 
		 * @return number of lies told
		 */
		public int getLies(){
			return numberOfLies;
		}
		
		/** 
		 * A string representation of the secret.
		 * 
		 * Overrides: toString in class Object
		 * 
		 * @return the string representation of secret followed by " (with X lies)", 
		 * 			where X > 1 is the number of times the user lied, 
		 * 			or by " (with 1 lie)" or by " (with no lie)"
		 */
		public String toString(){
			
			//return value
			String retVal =	userSecret.toString() + " (with ";
			
			//add specific retVal ending depending on lies
			if (numberOfLies > 1 ) 				
				retVal += numberOfLies + " lies)";
			else if(numberOfLies == 1)
				retVal += "1 lie)";
			else
				retVal += "no lie)";
			
			return retVal;
		}
		
	}
	
	/**
	 * 
	 *Sets an upper bound on the number of objects to be used in the guessing process. 
	 *By default, all the objects provided at construction time are used. 
	 *This methods selects a randomly chosen subset of objects of the specified size. 
	 *The selection relies on java.util.Collections.shuffle for randomness.
	 *
	 *For instance, if a Liar object is created with candidates {A,B,C,D} and selectCandidates(2) is called, 
	 *2 candidates are chosen (say, A and C) and used for the next game. 
	 *B and D are then not used at all and won't appear in any question. 
	 *selectCandidates() should be called after a game has finished and before the next game is initialized. 
	 *If called at other times, it throws an IllegalStateException.
	 *
	 *The method is most useful when a Liar instance is created with a large set (e.g., a dictionary of all English words) 
	 *but we care to play with only a few elements from this set (e.g., 10 words, chosen randomly)
	 * 
	 * @param n  the maximum number of objects to use
	 * @return  the actual number of objects to be used in the guessing game; it is equal to n unless the guesser was created with fewer objects
	 * 
	 * @throws IllegalStateException - if the object has been initialized and a guessing process is still going on
	 * @throws IllegalArgumentException - if n is less than 1
	 */	
	public int selectCandidates(int n){
		
		if(isInitialized)
			throw new IllegalStateException();
		
		if(n < 1)
			throw new IllegalArgumentException();		

		//just return number of candidates if n is bigger
		int retVal = n > allCandidates.size() ? allCandidates.size() : n;
		
		Collections.shuffle(allCandidates);
		
		//candidates holds all candidates for current game
		allCandidates = new ArrayList<>(allCandidates.subList(0, retVal));
		
		return retVal;
	}
	
	/**
	 * Builds a guesser that will find the secret object among a list of candidates, assuming a maximum number of lies.
	 * 
	 * @param candidates a list of objects, which includes the secret to be found 
	 * @param lies the maximum number of times a use can lie
	 * @param name a word that's used to refer to the objects from the list (string, object, animal, color, ...)
	 * 
	 * @throws IllegalArgumentException - if the set of candidates is empty, the number of lies is negative, or the name is null
	 */	
	public Liar(Set<? extends T> candidates, int lies, String name){
		
		if(candidates.isEmpty() || lies < 0 || name == null)
			throw new IllegalArgumentException();
		
		this.maxLies = lies;
		this.name = name;
		
		this.isInitialized = false;
		this.isSolved = false;
		this.questionAsked = false;
		
		//It took me far longer than I would like to admit to realize I can use a collection
		//in the constructor for an ArrayList. Special thanks to my boss for this one :)
		this.allCandidates = new ArrayList<>(candidates);		
	}


	/** Initializes the guessing engine.  This method must be called to
	   * initiate a problem before the rounds of questions and answers begin.
	   *
	   * @return An initialization message that can be displayed to the user
	   */
	public String initialize() {
		//because Initialize works as reset as well, all maps must be initialized here
				
		//For this algorithm, using TreeMap seems like the best choice. Maybe switch in future
		this.upperPile = new TreeMap<>();
		this.lowerPile = new TreeMap<>();
		
		//get total lies possible for progress calculation
		this.totalLiesPossible = allCandidates.size() * (maxLies + 1);
		
		//Split up candidates and add to first column in each pile
		int numOfCandidates = allCandidates.size();//for easier use, putting size into a variable
		this.upperPile.put(0, new ArrayList<>((allCandidates).subList(0,numOfCandidates/2)));
		this.lowerPile.put(0, new ArrayList<>((allCandidates).subList(numOfCandidates/2,numOfCandidates)));
		
		//add remaining "columns" in piles, one for each lie, and a dump column
		for(int i = 0; i <= maxLies; i++){
			this.upperPile.put(i+1, new ArrayList<T>());
			this.lowerPile.put(i+1, new ArrayList<T>());
		}	
				
		this.isInitialized = true;
		this.isSolved = false;
		this.questionAsked = false;
				
		String retVal = "Pick one among";
		
		for(T cand : allCandidates){
			retVal += " " + cand.toString();
		}		
		
		return retVal;
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
			throw new IllegalStateException();
		
		//When only one candidate is used, games is immediately solved
		if(allCandidates.size() == 1)
			isSolved = true;
		else{
			
			//first get amount of candidates remaining in non-dump columns
			int candidatesRemaining = 0;
			for(int i = 0; i <= maxLies; i++)
				candidatesRemaining += this.upperPile.get(i).size() + this.lowerPile.get(i).size();
				
			//there should never be 0 candidates remaining and if negative, something really went wrong.
			assert(candidatesRemaining > 0);
			
			if(candidatesRemaining > 1)
				isSolved = false;
			else
				isSolved = true;
		}
			
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
	public Secret<T> getSecret() {
		
		
		if(!isSolved || !isInitialized)
			throw new IllegalStateException();
		
		//will never reach this point with more than one candidate left
		Secret<T> retVal = null;
		
		//Find only remaining candidate, stop when found.
		for(int i = 0; i <= maxLies && retVal == null; i++){
			
			//i will always equal the number of lies.
			if(!upperPile.get(i).isEmpty())
				retVal = new Secret<>(i, upperPile.get(i).get(0));
			else if(!lowerPile.get(i).isEmpty())
				retVal = new Secret<>(i, lowerPile.get(i).get(0));	
			
		}		
		
		//if getting secret, game is over. Uninitialize.
		isInitialized = false;
		
		return retVal;
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
		
		//move bottom candidates to next column unless already in dump column
		//start at last lie column to prevent moving them all the way to the dump column
		for(int i = maxLies; i >= 0; i--){
			ArrayList<T> temp = new ArrayList<>(lowerPile.get(i));

			for(T candidate: temp){
				lowerPile.get(i + 1).add(candidate);
				lowerPile.get(i).remove(candidate);
			}
		}
		
		//evenly distribute items in columns, can ignore dump column
		//use this flag to prevent items in top and no items in bottom pile
		boolean putSingleInBottom = false;
		for(int i = 0; i <= maxLies; i++){
			ArrayList<T> currentColumnValues = new ArrayList<>();
			int numOfValues;
			
			ArrayList<T> temp = new ArrayList<>(upperPile.get(i));			
			for(T candidate: temp)
				currentColumnValues.add(candidate);
			
			temp = new ArrayList<>(lowerPile.get(i));
			for(T candidate: temp)
				currentColumnValues.add(candidate);
			
			upperPile.get(i).clear();
			lowerPile.get(i).clear();
			
			numOfValues = currentColumnValues.size();
			
			if(numOfValues > 1){
				upperPile.get(i).addAll(currentColumnValues.subList(0, (numOfValues + 1)/2));
				lowerPile.get(i).addAll(currentColumnValues.subList((numOfValues + 1)/2 , numOfValues));
			}
			else if(numOfValues == 1 && putSingleInBottom){
				lowerPile.get(i).addAll(currentColumnValues);
				putSingleInBottom = false;
			}
			else if(numOfValues == 1 && !putSingleInBottom){
				upperPile.get(i).addAll(currentColumnValues);
				putSingleInBottom = true;
			}
		}

		questionAsked = false;
		numOfQuestions++;
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
		
		//move top candidates to next column unless already in dump column
		//start at last lie column to prevent moving them all the way to the dump column
		for(int i = maxLies; i >= 0; i--){
			ArrayList<T> temp = new ArrayList<>(upperPile.get(i));

			for(T candidate: temp){
				upperPile.get(i + 1).add(candidate);
				upperPile.get(i).remove(candidate);
			}
		}
		
		//evenly distribute items in columns, can ignore dump column
		//use this flag to prevent items in top and no items in bottom pile
		boolean putSingleInBottom = false;		
		for(int i = 0; i <= maxLies; i++){
			ArrayList<T> currentColumnValues = new ArrayList<>();
			int numOfValues;
			
			ArrayList<T> temp = new ArrayList<>(upperPile.get(i));			
			for(T candidate: temp)
				currentColumnValues.add(candidate);
			
			temp = new ArrayList<>(lowerPile.get(i));
			for(T candidate: temp)
				currentColumnValues.add(candidate);
			
			upperPile.get(i).clear();
			lowerPile.get(i).clear();
			
			numOfValues = currentColumnValues.size();
			
			if(numOfValues > 1){
				upperPile.get(i).addAll(currentColumnValues.subList(0, (numOfValues + 1)/2));
				lowerPile.get(i).addAll(currentColumnValues.subList((numOfValues + 1)/2 , numOfValues));
			}
			else if(numOfValues == 1 && putSingleInBottom){
				lowerPile.get(i).addAll(currentColumnValues);
				putSingleInBottom = false;
			}
			else if(numOfValues == 1 && !putSingleInBottom){
				upperPile.get(i).addAll(currentColumnValues);
				putSingleInBottom = true;
			}
		}

		questionAsked = false;
		numOfQuestions++;
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
		
		String question = "Is the secret " + this.name + " among";
		
		//Add all the candidates in the upper pile and not in dump pile
		for(int i = 0; i <= maxLies; i++){
			for(T candidate: upperPile.get(i))
				question += " " + candidate.toString();
		}			
		
		question += "?";
		questionAsked = true;
		
		return question;
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
			throw new IllegalStateException();
		
		//double check if solved		
		hasSolved();		
		
		//if solved, just return 1.0
		if(isSolved)
			return 1.0;
		
		//not sure best way to get progress so I got it by calculating the sum of total lies remaining per candidate
		//and divide it by the total at the start
		double currentLiesRemaining = 0;
		
		for(int i = 0; i <= maxLies; i++){
			
			//formula for lies remaining for column: numOfValues * (maxLies - (liesTold - 1))
			currentLiesRemaining += (double)upperPile.get(i).size() * (double)(maxLies - (i - 1));
			currentLiesRemaining += (double)lowerPile.get(i).size() * (double)(maxLies - (i - 1));
		}
		
		
		return (1.0 - currentLiesRemaining/totalLiesPossible);
	}
	
}
