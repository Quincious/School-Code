package cs671.pig.server;

import cs671.pig.Strategy;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;

/**
 * Created by Jonathan Hart.
 */
public class StrategyToProtocol implements Runnable{

    Strategy strategy;
    BufferedWriter output;
    BufferedReader input;
	boolean endPlay;
    Object endObj = new Object();

    public StrategyToProtocol(Strategy s, BufferedReader in, BufferedWriter out){
        strategy = s;
        input = in;
        output = out;
		endPlay = false;
    }
	
	public void endPlay(){
        synchronized (endObj){
            endPlay = true;
        }
    }

    private boolean isRunning(){

        synchronized (endObj){
            return endPlay;
        }
    }

    public void run() {

        String recv;
        Message msg;
        try{

            while(isRunning()){

                recv = input.readLine();
                msg = Message.parse(recv);

                if (msg.header != Message.Header.START) {
                    System.err.printf("Server is crazy; instead of START, it said: '%s'%n", msg);
                    return;
                }

                if(strategy.startGame(msg.equals(Message.START_YES)))
                    Message.START_YES.send(output);
                else{
                    Message.START_NO.send(output);
                    break;
                }

                while(isRunning()){

                    recv = input.readLine();
                    msg = Message.parse(recv);

                    if(msg.header.equals(Message.Header.DICE)){
                        String dice = msg.content.trim();
                        int[] intDice = new int[dice.length()];
                        for(int i = 0; i < dice.length(); i++)
                            intDice[i] = Character.digit(dice.charAt(i), 10);

                        strategy.opponentPlay(intDice,intDice.length);
                    }else if (msg.header.equals(Message.Header.DIE)){

                        if(msg.content.equals("1"))
                            strategy.roll(Integer.parseInt(msg.content));
                        else if(strategy.roll(Integer.parseInt(msg.content)))
                            Message.DECIDE_ROLL.send(output);
                        else
                            Message.DECIDE_HOLD.send(output);
                    }else if (msg.header.equals(Message.Header.END)){
                        String[] scores = msg.content.split("/");
                        if(Integer.parseInt(scores[0]) > Integer.parseInt(scores[1])){
                            String info = "You won! " + msg.content;
                            strategy.endGame(info);
                        }else{
                            String info = "You lost! " + msg.content;
                            strategy.endGame(info);
                        }
                        break;
                    }
                    else{
                        System.err.printf("Server is crazy; instead of DICE, DIE or END, it said: '%s'%n", msg);
                        return;
                    }
                }
            }

        } catch (IOException e) {
            strategy.endGame(e.getMessage());
        } catch (Message.Exception e) {
            strategy.endGame(e.getMessage());
        }

    }
}
