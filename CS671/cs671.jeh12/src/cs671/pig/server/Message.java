package cs671.pig.server;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;

/**
 * Created by Jonathan Hart.
 */
public class Message {

    public final String content;
    public final Message.Header header;
    public static final Message DECIDE_ROLL = new Message(Header.DECIDE, "ROLL");
    public static final Message DECIDE_HOLD = new Message(Header.DECIDE, "HOLD");
    public static final Message START_YES = new Message(Header.START, "YES");
    public static final Message START_NO = new Message(Header.START, "NO");
    public static final Message INIT = new Message(Header.INIT, "");

    public static enum Header{
        ERROR, DECIDE, INIT, DIE, DICE, START, END;
    }

    public static class Exception extends java.lang.Exception{

        Exception(String s){
            super(s);
        }

        Exception(Throwable cause) {
            super(cause);
        }
    }

    Message(Header head, String msg){
        header = head;
        content = msg;
    }

    public String toString(){

        String newContent = content.replace('\n', '\00');

        return header.name() + ":" + newContent;
    }

    public boolean equals(Message m){
        return m == this || this.content.equals(m.content);
    }

    public boolean equals(Object o){
        return o instanceof Message && this.equals((Message)o);
    }

    public int hashCode(){
        return content.hashCode();
    }

    public static Message makeERROR(String msg){
        if(msg.contains("\00"))
            throw new IllegalArgumentException();

        String newMsg = msg.replace('\00', '\n');

        return new Message(Header.ERROR, newMsg);
    }

    public static Message makeINIT(String msg){
        if(msg.contains("\00"))
            throw new IllegalArgumentException();

        String newMsg = msg.replace('\00', '\n');

        return new Message(Header.INIT, newMsg);
    }

    public static Message makeEND(String msg){
        if(msg.contains("\00"))
            throw new IllegalArgumentException();

        String newMsg = msg.replace('\00', '\n');

        return new Message(Header.END, newMsg);
    }

    public static Message makeDIE(int n){
        if(n < 1 || n > 6)
            throw new IllegalArgumentException();

        return new Message(Header.DIE, String.valueOf(n));
    }

    public static Message makeDICE(int[] a, int l){
        if(a.length == 0 || l == 0)
            throw new IllegalArgumentException();

        for(int i = 0; i < l; i++)
            if(a[i] < 1 || a[i] > 6) throw new IllegalArgumentException();

        String msg = String.valueOf(a[0]);

        for(int i = 1; i < l; i++)
            msg += " " + String.valueOf(a[i]);

        return new Message(Header.DICE, msg);
    }

    public static Message parse(String s) throws Message.Exception{
        if(s.contains("\n"))
            throw new IllegalArgumentException();

        String[] strings = s.split(":");

        if(strings.length == 1 && strings[0] != "INIT")
            return INIT;

        String newString = strings[1].replace('\00', '\n');

        switch(strings[0]){
            case "INIT":
                newString = s.substring(5).replace('\00', '\n');
                return new Message(Header.INIT, newString);
            case "DECIDE":
                if(newString.trim().equals("HOLD"))
                    return DECIDE_HOLD;
                else if(newString.trim().equals("ROLL"))
                    return DECIDE_ROLL;
                else
                    throw new Exception("Invalid DECIDE message received: " + s);
            case "ERROR":
                return new Message(Header.ERROR, newString);
            case "DIE":
                if(tryParseInt(newString.trim()))
                    return new Message(Header.DIE, newString);
                else
                    throw new Exception("Invalid DIE message received: " + s);
            case "DICE":
                String compStr = newString.trim();
                boolean foundOne = false;
                for(int i = 0; i < compStr.length(); i++){
                    char c = compStr.charAt(i);

                    if(!Character.isDigit(c) || foundOne)
                        throw new Exception("Invalid DICE message received: " + s);

                    int digit = Character.digit(c, 10);

                    if(digit == 1)
                        foundOne = true;
                    else if(digit > 6 || digit < 1)
                        throw new Exception("Invalid DICE message received: " + s);
                }

                return new Message(Header.DICE, newString);
            case "START":
                if(newString.trim().equals("YES"))
                    return START_YES;
                else if(newString.trim().equals("NO"))
                    return START_NO;
                else
                    throw new Exception("Invalid START message received: " + s);
            case "END":
                String[] scores = newString.trim().split("/");
                if(scores.length > 2 || !tryParseInt(scores[0]) || !tryParseInt(scores[1]))
                    throw new Exception("Invalid END message received: " + s);
                else
                    return new Message(Header.END, newString);

            default:
                throw new Exception("Invalid message received(Header): " + s);

        }
    }

    public static Message read(BufferedReader r) throws Message.Exception{

        String recvMsg;
        try{
            recvMsg = r.readLine();
            return parse(recvMsg);
        } catch (IOException e) {
            throw new Exception(e.getCause());
        }
    }

    public void send(BufferedWriter w) throws Message.Exception{

        String msg = this.toString();
        try{
            w.write(msg + "\n");
            w.flush();
        } catch (IOException e) {
            throw new Exception(e.getCause());
        }

    }

    private static boolean tryParseInt(String value){
        try{
            Integer.parseInt(value);
            return true;
        }catch (NumberFormatException ex){
            return false;
        }
    }

}
