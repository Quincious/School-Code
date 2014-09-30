package cs671.pig.server;

import cs671.pig.Competition;
import cs671.pig.Strategy;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

/**
 * Created by Jonathan Hart.
 */
public class MatchMaker {
    public static final int LIMIT = 10;
    int port;
    boolean running;
    Object runLock = new Object();

    HashMap<String,Socket> clientList;

    ServerSocket server;

    public MatchMaker(int port){
        this.port = port;
        running = false;
        clientList = new HashMap<>();
    }

    public void start(){
        synchronized (runLock){
            if(running)
                throw new IllegalStateException();

            running = true;
        }
        try{
            server = new ServerSocket(port);

            while(isRunning()){

                Socket client = server.accept();

                BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
                BufferedWriter out = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()));

                try {
                    Message msg = Message.makeINIT("Welcome to Jon's Matchmaker for a game of Pig!");
                    msg.send(out);
                    msg = Message.read(in);
                    if (msg.header == Message.Header.ERROR){
                        System.err.println(msg.toString());
                        continue;
                    }
                    if(msg.header != Message.Header.INIT){
                        System.err.println("Not INIT: " + msg.toString());
                        continue;
                    }

                    String name = msg.content;
                    if(!isValidName(name)){
                        System.err.println("Invalid Name: " + msg.toString());
                        continue;
                    }

                    Set<String> players = clientList.keySet();
                    String playerList = "";

                    for(String playerName : players)
                        playerList += playerName + ",";

                    if(playerList.endsWith(","))
                        playerList = playerList.substring(0, playerList.length()-1);

                    msg = Message.makeINIT(playerList);
                    msg.send(out);
                    msg = Message.read(in);
                    if (msg.header == Message.Header.ERROR){
                        System.err.println(msg.toString());
                        continue;
                    }
                    if(msg.header != Message.Header.INIT){
                        System.err.println("Not INIT: " + msg.toString());
                        continue;
                    }

                    if(msg.equals(Message.INIT)){
                        clientList.put(name, client);
                        continue;
                    }

                    if(!clientList.containsKey(msg.content)){
                        System.err.println("No player with name: " + msg.toString());
                        continue;
                    }

                    String client2Name = msg.content;
                    Socket client2 = clientList.remove(client2Name);

                    BufferedReader in2 = new BufferedReader(new InputStreamReader(client2.getInputStream()));
                    BufferedWriter out2 = new BufferedWriter(new OutputStreamWriter(client2.getOutputStream()));

                    Strategy p1 = new ProtocolToStrategy(name, in, out);
                    Strategy p2 = new ProtocolToStrategy(client2Name, in2, out2);

                    final Competition comp = new Competition(p1,p2);

                    new Thread(new Runnable() {
                        @Override
                        public void run() {
                            comp.play(LIMIT);
                        }
                    }).start();
                } catch (Message.Exception e) {
                    e.printStackTrace();
                }

            }

            server.close();
        } catch (IOException e) {
            e.printStackTrace();
        }


    }

    public void stop(){
        synchronized (runLock){
            running = false;
        }
    }

    public static boolean isValidName(String name){
        return !name.isEmpty() && name != null && !name.contains("\n") && !name.contains(",");
    }

    public static void main(String[] args){
        int portNumber = Integer.parseInt(args[0]);

        MatchMaker mm = new MatchMaker(portNumber);

    }

    private boolean isRunning(){

        synchronized (runLock){
            return running;
        }
    }
}
