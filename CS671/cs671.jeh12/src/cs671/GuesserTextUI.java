// $Id: GuesserTextUI.java 856 2013-11-06 15:38:08Z charpov $

package cs671;

import java.util.*;
import java.io.*;

/** Stub of the text-based user interface for guessing games. */
public class GuesserTextUI {

	/**
	 * Class private variables
	 */
	private Scanner userInput;
	private PrintWriter userOutput;
	private Guesser<?> guesserInstance;
	
  /** Builds a user interface for the given guesser.  Questions are
   *  displayed on <code>output</code> and user input is read from
   *  <code>input</code>.
   */
   public GuesserTextUI
    (Guesser<?> g, java.io.Reader input, java.io.Writer output) {
     
	   guesserInstance = g; 
	   userInput = new Scanner(input);
	   userOutput = new PrintWriter(output,true);
  }

  /** Builds a user interface for the given guesser.  Questions are
   *  displayed on <code>System.out</code> and user input is read from
   *  <code>System.in</code>.
   */
   public GuesserTextUI (Guesser<?> g) {
	   guesserInstance = g;
     
     //Uses Sytem.in and System.out, Convert to Scanner and PrintWriter for easier use
     //Possibly try to find a better way to convert this for output
     userInput = new Scanner(System.in);
     userOutput = new PrintWriter(new OutputStreamWriter(System.out), true);
  }

  /**
   * Starts the interaction with the user. This method will only return when the user is done playing.
   * 
   *'y' (followed by a newline) is accepted as a valid input for 'yes'; similarly, 'n' means 'no'. 
   *This implementation accepts other answers such as 'Y', 'N', 'yes', 'no', etc. 
   *
   *Invalid answers from the user do not end the interaction. Instead, the method keeps asking until it gets a yes or no.
   *
   *Upon termination, this method flushes the output writer but does not close it, nor does it close the input reader.   * 
   * 
   * @return number of games played
   */
  public int play (){
	  
	  boolean running = true;//true when user is playing, false when user finished
	  int gamesPlayed = 0;//number of games played
	  	  
	  while(running){
		  
		  //initialize guesser at beginning of every game
		  String initialized = guesserInstance.initialize();
		  userOutput.println(initialized);
		  
		  //begin asking questions until answer is obtained
		  while(!guesserInstance.hasSolved()){
			  
			  boolean userAnswered = false;//to track if user answered properly
			  
			  //get question. Kept in variable so it can be reasked
			  String question = guesserInstance.makeQuestion();
			  
			  do{
				  userOutput.println(question);
				  
				  //get answer and put in variable to test
				  String answer = userInput.nextLine();
				  //convert to lowercase for easier testing
				  answer = answer.toLowerCase();
				  
				  //test user response
				  if(answer.equals("n") || answer.equals("no")){
					  guesserInstance.no();
					  userAnswered = true;
				  }
				  else if(answer.equals("y") || answer.equals("yes")){
					  guesserInstance.yes();
					  userAnswered = true;
				  }				  
				  
				  //if user response was not valid, ask again
			  }while(!userAnswered);
			  
			  //get progress output
			  String progressReport = String.format("I'm %.0f%% complete", guesserInstance.progress()*100.0);
			  
			  userOutput.println(progressReport);
			  
		  }
		  //Secret has been found		  
		  //get secret and convert to string because HiLo and Liar use different types
		  String userSecret = guesserInstance.getSecret().toString();
		  
		  userOutput.println("Your secret is " + userSecret);
		  
		  gamesPlayed++;
		  
		  boolean playAgainResponse = false; //Flag to test play again response
		  
		  do{
			  userOutput.println("Play Again?");
			  
			  String userResponse = userInput.nextLine();
			  userResponse = userResponse.toLowerCase();
			  
			  //test user response
			  if(userResponse.equals("n") || userResponse.equals("no")){
				  running = false;
				  playAgainResponse = true;
			  }
			  else if(userResponse.equals("y") || userResponse.equals("yes"))
				  playAgainResponse = true;
			  
			  
		  }while(!playAgainResponse);
	  }	  
	  
	  return gamesPlayed;
  }

  private static void usage () {
    System.err.println
      ("Usage: TextUI -hilo min max\n"+
       "   or: TextUI -liar #lies name1 [name2 ...]\n"+
       "   or: TextUI -liar #lies -file filename #names");
  }

  /** Starts a command-line program.  This program can be started in 3
   * different ways:
   *<pre>
   * Usage: TextUI -hilo min max
   *    or: TextUI -liar #lies name1 [name2 ...]
   *    or: TextUI -liar #lies -file filename #names
   *</pre>
   *
   * The last form takes the names of the secret objects from a file
   * and the last parameter specifies how many of these are actually used in
   * the game.
   *
   * @param args command-line parameters
   * @see Liar#selectCandidates
   * @throws java.io.IOException if the file of names cannot be opened and read
   */
  public static void main (String[] args) throws java.io.IOException {
    if (args.length < 3) {
      usage();
      return;
    }
    Guesser<?> guesser = null;
    if (args[0].equals("-hilo"))
      guesser = makeHiLoGuesser(args);
    else if (args[0].equals("-liar"))
      guesser = makeLiarGuesser(args); // args.length > 2
    if (guesser == null) {
      usage();
      return;
    }
    int n = new GuesserTextUI(guesser).play();
    System.out.printf("(%d game", n);
    if (n > 1)
      System.out.printf("s");
    System.out.println(" played)");
  }

  /**
   * 
   * @param args command-line params
   * @return instance of guesser
   */
  private static Guesser<Integer> makeHiLoGuesser (String[] args) {
	  
	  int min = Integer.parseInt(args[1]);
	  int max = Integer.parseInt(args[2]);
	  
	  Guesser<Integer> newHiLoGame = new HiLo<Integer>(min, max);
	  	  
	  return newHiLoGame;
  }

  // to be implemented
  private static Guesser<Liar.Secret<String>> makeLiarGuesser (String[] args) {
	  
	  //type of set essentially irrelevant so just using HashSet
	  Set<String> candidates = new HashSet<String>();
	  String name = "string";//not sure if I should be putting something else here or not
	  int maxLies = Integer.parseInt(args[1]);	  
	  
	  if(args[2].equals("-file")){
		  
		  try{
			  
			  File inFile = new File(args[3]);
			  int numOfNames = Integer.parseInt(args[4]);
			  
			  Scanner scan = new Scanner(inFile);
			  
			  while(scan.hasNextLine()){
				  
				  Scanner scan2 = new Scanner(scan.nextLine());
				  
				  while(scan2.hasNext())
					  candidates.add(scan2.next());
				  
				  scan2.close();				  				  
			  }
			  
			  scan.close();
			  
			  Liar<String> newLiarGame = new Liar<String>(candidates, maxLies, name);
			  newLiarGame.selectCandidates(numOfNames);
			  
			  return newLiarGame;			  
		  }
		  catch(Exception ex){
			  System.out.println(ex.toString());
			  return null;
		  }		  	  
	  }
	  else{
		  
		  for(int i = 2; i < args.length; i++)
			  candidates.add(args[i]);
		  
		  Liar<String> newLiarGame = new Liar<String>(candidates, maxLies, name);
		  
		  return newLiarGame;
	  }
  }
}
