package cs671.pig;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.util.Scanner;

/**
 * Created by Jonathan Hart.
 */
public class UserTerminalStrategy implements Strategy {

    Scanner in;
    PrintStream out;
    String name;
    int totalScore;
    int roundScore;
    int opponentScore;

    boolean thisPlayerTurn;
    boolean gameStarted;

    public UserTerminalStrategy(String name){
        this.name = name;
        in = new Scanner(System.in);
        out = System.out;
        totalScore = 0;
        roundScore = 0;
        opponentScore = 0;
        thisPlayerTurn = false;
        gameStarted = false;
    }

    /** Decides on a roll.
     * @param value the value of the die
     * @return true to roll, false to hold
     * @throws IllegalStateException if called at a time that is
     * inconsistent with the rules of the game
     */
    public boolean roll (int value){

        if(!thisPlayerTurn)
            throw new IllegalStateException();

        if(value == 1){
            out.print("You roll 1. You lose your turn. Press return to continue.");
            in.nextLine();
            out.print("\n");
            roundScore = 0;
            thisPlayerTurn = false;
            return false;
        }

        roundScore += value;
        boolean validAnswer = false;
        boolean retVal = false;

        do{
            out.print("\nYou roll " + value + "\tYour score is " + totalScore + "+" + roundScore + "=" + (totalScore + roundScore) +
                "\tWhats your decision (r/h)? ");

            String resp = in.nextLine();

            if(resp.equals("h")){
                retVal = false;
                validAnswer = true;
                totalScore += roundScore;
                thisPlayerTurn = false;
                roundScore = 0;
            }else if(resp.equals("r")){
                retVal = true;
                validAnswer = true;
            }else{
                out.print("\nInvalid response. Respond with r or h.\n");
            }

        }while(!validAnswer);

        return retVal;
    }

    /** Analyses the oponent play.
     * @param values an array of dice values, only the first {@code
     * count} of which are used
     * @param count the number of times the opponent rolled the die
     * @throws IllegalStateException if called at a time that is
     * inconsistent with the rules of the game
     * @throws IllegalArgumentException if {@code count < 1}, {@code
     * values.length < count}, values contains numbers smaller than 1 or
     * larger than 6, or values contain 1 in a position other than the
     * last.
     */
    public void opponentPlay (int[] values, int count){

        if(count < 1 || values.length < count)
            throw new IllegalArgumentException();

        if(thisPlayerTurn)
            throw new IllegalStateException();

        boolean foundOne = false;
        int oppRoundScore = 0;

        out.print("Your opponent plays: ");

        for(int i = 0; i < count; i++){
            if(foundOne || values[i] < 1 || values[i] > 6)
                throw new IllegalArgumentException();

            if(values[i] == 1)
                foundOne = true;

            oppRoundScore += values[i];

            out.print(values[i] + " ");
        }

        if(!foundOne){
            opponentScore += oppRoundScore;
            out.print("\tHis/her/its score is now " + opponentScore + ".\n\n");
        }else{
            out.print("\tHis/her/its score stays at " + opponentScore + ".\n\n");
        }

        thisPlayerTurn = true;
    }

    /** Starts a new game.
     * @param iStart is true iff this player plays first (i.e., it is
     * false for the other player).
     * @return true if this strategy accepts to play another game, false otherwise
     */
    public boolean startGame (boolean iStart){

        boolean validAnswer = false;
        boolean retVal = false;

        do{
            out.print("\nDo you want to start a new game (you will ");
            if(!iStart)
                out.print("not ");
            out.print("play first)? ");

            String resp = in.nextLine();

            if(resp.equals("y")){
                retVal = true;
                validAnswer = true;
            }else if(resp.equals("n")){
                retVal = false;
                validAnswer = true;
            }else{
                out.print("\nInvalid response. Respond with y or n.\n");
            }

        }while(!validAnswer);

        gameStarted = true;
        thisPlayerTurn = iStart;

        return retVal;
    }

    /** Ends a game.
     * @param info comments on the game from the the authority that ran it
     */
    public void endGame (String info){
        gameStarted = false;
        totalScore = 0;
        roundScore = 0;
        opponentScore = 0;
        out.print("\nThe game is over. Info: " + info + ".\n");
    }

    /** The name of this strategy. */
    public String getName (){
        return name;
    }
}
