package cs671.pig.server;

import cs671.pig.Strategy;

import java.io.BufferedReader;
import java.io.BufferedWriter;

/**
 * Created by Jonathan Hart.
 */
public class ProtocolToStrategy implements Strategy {

    String name;
    BufferedWriter writer;
    BufferedReader reader;
    int totalScore;
    int roundScore;
    int opponentScore;

    boolean thisPlayerTurn;
    boolean gameStarted;

    public ProtocolToStrategy(String name, BufferedReader in, BufferedWriter out){
        this.name = name;
        writer = out;
        reader = in;
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
            try {
                Message.makeDIE(1).send(writer);
                roundScore = 0;
                thisPlayerTurn = false;
                return false;
            } catch (Message.Exception e) {
                e.printStackTrace();
                return false;
            }
        }

        roundScore += value;

        Message msg = Message.makeDIE(value);
        try {
            msg.send(writer);
            msg = Message.read(reader);
            if(msg.equals(Message.DECIDE_ROLL))
                return true;
            else{
                totalScore += roundScore;
                roundScore = 0;
                thisPlayerTurn = false;
                return false;
            }

        } catch (Message.Exception e) {
            return false;
        }

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

        try {

            for(int i = 0; i < count; i++){
                if(foundOne || values[i] < 1 || values[i] > 6)
                    throw new IllegalArgumentException();

                if(values[i] == 1)
                    foundOne = true;

                oppRoundScore += values[i];

            }

            if(!foundOne)
                opponentScore += oppRoundScore;

            Message.makeDICE(values,count).send(writer);
        } catch (Message.Exception e) {
            e.printStackTrace();
        }

        thisPlayerTurn = true;
    }


    /** Starts a new game.
     * @param iStart is true iff this player plays first (i.e., it is
     * false for the other player).
     * @return true if this strategy accepts to play another game, false otherwise
     */
    public boolean startGame (boolean iStart){
        boolean retVal = false;


        try{
            if(!iStart)
                Message.START_NO.send(writer);
            else
                Message.START_YES.send(writer);

            gameStarted = true;
            thisPlayerTurn = iStart;

            return Message.read(reader).equals(Message.START_YES);

        } catch (Message.Exception e) {
            e.printStackTrace();
            return false;
        }

    }

    /** Ends a game.
     * @param info comments on the game from the the authority that ran it
     */
    public void endGame (String info){
        gameStarted = false;
        try {
            Message.makeEND(info).send(writer);
        } catch (Message.Exception e) {
            e.printStackTrace();
        }
    }

    /** The name of this strategy. */
    public String getName (){
        return name;
    }

}
