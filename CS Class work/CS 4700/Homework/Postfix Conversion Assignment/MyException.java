/*
 * MyException.java
 *
 * Created on November 1, 2001, 10:39 AM
 */



/**
 *
 * @author  marks
 * @version 
 */
public class MyException extends Exception {

    /**
     * Creates new <code>MyException</code> without detail message.
     */
    public MyException() {
    }


    /**
     * Constructs an <code>MyException</code> with the specified detail message.
     * @param msg the detail message.
     */
    public MyException(String msg) {
        super(msg);
    }
}

