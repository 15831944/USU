/*
 * JInternalFrame.java
 *
 * Created on March 22, 2002, 3:58 PM
 */

/**
 *
 * @author  Default
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.*;
import javax.swing.text.StyledEditorKit.StyledTextAction.*;
import java.awt.dnd.*;
import java.awt.datatransfer.*;
import java.io.File;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.awt.print.*;

public class DocumentWindow extends javax.swing.JInternalFrame 
                            implements InternalFrameListener, 
                            ActionListener, 
                            CaretListener,
                            DragGestureListener,
                            DragSourceListener,
                            DropTargetListener,
                            MouseListener
{
    JMenuItem windowMenuItem;
    JApplet parent;
    //public RTFEditorKit editorKit;
    public JTextPane textPane;
    public LimitedStyledDocument lsd;
    String newline = "\n";
    static final int MAX_CHARACTERS = 10000;
    boolean documentModified = false;
    // support for drag and drop
    DragSource dragSource;
    //DragGestureListener dgListener;
    //DragSourceListener dsListener;
    int dragAction = DnDConstants.ACTION_COPY;
    boolean dragReady = false;
    public String filename = null;
    
    public void setMenuItem(JMenuItem menuItem)
    {
        windowMenuItem = menuItem;
    }
    public JMenuItem getMenuItem()
    {
        return windowMenuItem;
    }
    
    /** Creates new form JInternalFrame */
    public DocumentWindow(JApplet pComponent, String title, String FileName) 
    {
        parent = pComponent;
        setTitle(title);
        initComponents();
        //Put the initial text into the text pane.
        filename = FileName;
        if (filename != null)
        {
            initDocument(filename);
        }
    }

    private void initComponents() 
    {
        setMaximizable(true);
        setIconifiable(true);
        setResizable(true);
        setClosable(true);
        setPreferredSize(new java.awt.Dimension(300, 250));
        addInternalFrameListener(this);
        
        lsd = new LimitedStyledDocument(MAX_CHARACTERS);
        textPane = new JTextPane(lsd);  
        //editorKit = new RTFEditorKit();
        //textPane.setEditorKit(editorKit);
        textPane.setCaretPosition(0);
        textPane.setMargin(new Insets(5,5,5,5));
        JScrollPane scrollPane = new JScrollPane(textPane);
        
        //Add the components to the frame.
        JPanel contentPane = new JPanel(new BorderLayout());
        contentPane.add(scrollPane, BorderLayout.CENTER);
        setContentPane(contentPane);
        
        textPane.addCaretListener(this);
        lsd.addDocumentListener(new MyDocumentListener());
        
        pack();
        
        // start support for dragging
        dragSource = DragSource.getDefaultDragSource();
        // component, action, listener
        dragSource.createDefaultDragGestureRecognizer(textPane,dragAction,this); 
        textPane.addMouseListener(this);
        //((JTextComponent)textPane).setDragEnabled(true);
        
    }
    
    protected void initDocument(String fileName) 
    {
        try 
        {
            BufferedReader in = new BufferedReader(new FileReader(fileName));
            String thisLine;
            
            try 
            {
                while ((thisLine = in.readLine()) != null)
                {
                    lsd.insertString(lsd.getLength(), thisLine + newline,
                        new SimpleAttributeSet());
                }
            } 
            catch (BadLocationException ble) 
            {
                System.err.println("Couldn't insert initial text.");
            }
        }
        catch (Exception e)
        {

        }
                
        
    }
    
    public void documentSave()
    {
        System.out.println("Saving document to file "+filename);
        if (filename != null)
        {
            Segment textBuffer = new Segment();
            try 
            {
                lsd.getText(0,lsd.getLength(),textBuffer);
                String sText = textBuffer.toString();
                try 
                {
                    BufferedWriter out = new BufferedWriter(new FileWriter(filename));
                    out.write(sText);
                    out.close();
                } 
                catch (Exception e) 
                {
                    e.printStackTrace();
                }
                documentModified = false;
            }
            catch (BadLocationException e)
            {
                e.printStackTrace();
            }
            return;
        }
        
        
    }
    
    public void documentSaveAs()
    {
        final JFileChooser fc = new JFileChooser();
        int returnVal = fc.showSaveDialog(this);
        
        if(returnVal == JFileChooser.APPROVE_OPTION)
        {
            filename = fc.getSelectedFile().getPath();
            setTitle(filename);
            documentSave();
            parent.removeDocumentFromWindowMenu(this);
            parent.addDocumentToWindowMenu(filename,this);
        }
    }
    
    //This listens for and reports caret movements.
    public void caretUpdate(CaretEvent e) 
    {
        //Get the location in the text.
        int dot = e.getDot();
        int mark = e.getMark();

        if (dot < mark) 
        {
            System.out.println("selection from: " + dot
                    + " to " + mark + newline);
        } 
        else if (mark < dot)
        {
            System.out.println("selection from: " + mark
                    + " to " + dot + newline);
        }
    }

    //And this one listens for any changes to the document.
    protected class MyDocumentListener
                    implements DocumentListener 
    {
        public void insertUpdate(DocumentEvent e) 
        {
            genericUpdate(e);
        }
        public void removeUpdate(DocumentEvent e) 
        {
            genericUpdate(e);
        }
        public void changedUpdate(DocumentEvent e) 
        {
            genericUpdate(e);
        }
        private void genericUpdate(DocumentEvent e) 
        {
            //Document doc = (Document)e.getDocument();
            //int changeLength = e.getLength();
            //changeLog.append(e.getType().toString() + ": " +
            //    changeLength + " character" +
            //    ((changeLength == 1) ? ". " : "s. ") +
            //    " Text length = " + doc.getLength() + "." + newline);
            documentModified = true;
        }
    }
    
    //////////////////////////////////////////////////////////////////////////
    // InternalFrameListener interface implementation
    //////////////////////////////////////////////////////////////////////////
    public void internalFrameClosing(InternalFrameEvent e) 
    {
        if (documentModified)
        {
            if (JOptionPane.showInternalConfirmDialog(this, getTitle() + " has been modified.  Would you like to save before closing?","File Not Saved",JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION)
            {
                if (filename != null)
                {
                    documentSave();
                }
                else
                {
                    documentSaveAs();
                }
                //System.out.println("user confirmed save");
            }
        }
        parent.removeDocumentFromWindowMenu(this);
        parent.openDocumentCount--;
        
        displayMessage("Internal frame closing",e);  
    }

    public void internalFrameClosed(InternalFrameEvent e) 
    {
        displayMessage("Internal frame closed",e);
        //listenedToWindow = null;
    }

    public void internalFrameOpened(InternalFrameEvent e) 
    {
        //XXX: We don't seem to get any of these.
        displayMessage("Internal frame opened",e);
    }

    public void internalFrameIconified(InternalFrameEvent e) 
    {
        displayMessage("Internal frame iconified", e);
    }

    public void internalFrameDeiconified(InternalFrameEvent e) 
    {
        displayMessage("Internal frame deiconified", e);
    }

    public void internalFrameActivated(InternalFrameEvent e) 
    {
        displayMessage("Internal frame activated", e);
    }

    public void internalFrameDeactivated(InternalFrameEvent e) 
    {
        displayMessage("Internal frame deactivated", e);
    }

    void displayMessage(String prefix, InternalFrameEvent e) 
    {
        //String s = prefix + ": " + e.getSource(); 
        //display.append(s + newline);
        //System.out.println(s);
    }

    public void actionPerformed(ActionEvent e) 
    {
        //if (e.getActionCommand().equals(SHOW)) {
            //XXX: Can't reuse internal frame (bug 4138031).
            //listenedToWindow.setVisible(true)
    }

    ///////////////////////////////////////////////////////////////////////////
    // Drag and Drop Listeners
    ///////////////////////////////////////////////////////////////////////////
    /*
    public void dragGestureRecognized(DragGestureEvent e) 
    {
        System.out.println(e.getDragAction());
        System.out.println( "kicking off drag");
      
        // get the label's text and put it inside a Transferable
        Transferable transferable = new StringTransferable( textPane.getSelectedText() );      

        // now kick off the drag
        try 
        {
	    // initial cursor, transferrable, dsource listener
	    e.startDrag(DragSource.DefaultCopyDrop,
	        transferable,
	        dsListener);

	    // for a drag image
	    
	    //if(DragSource.isDragImageSupported() )
	    // cursor, image, point, transferrable, dsource listener	
	    //e.startDrag(DragSource.DefaultCopyDrop, image, point, transferable, dsListener);
	    
	
        } 
        catch ( InvalidDnDOperationException idoe ) 
        {
	    System.err.println( idoe );
        }
    }
  
  
    //
    // DSListener
    // a listener that will track the state of the DnD operation
    // @see java.awt.dnd.DragSourceListener
    // @see java.awt.dnd.DragSource
    // @see java.awt.datatransfer.StringSelection      
    //
  
    
    
    public void dragDropEnd(DragSourceDropEvent e) 
    {
        if( e.getDropSuccess() == false ) 
        {
	    System.out.println( "not successful");
	    return;
        }

        //the dropAction should be what the drop target specified
        //in acceptDrop
        
        System.out.println( "dragdropend action " + e.getDropAction() );

      // this is the action selected by the drop target
        if (e.getDropAction() == DnDConstants.ACTION_MOVE)
        {
            // here is where we would clear the selection in the source...
	    //DragLabel.this.setText("");
        }
    }

    
    public void dragEnter(DragSourceDragEvent e) 
    {
      System.out.println( "draglabel enter " + e);
      DragSourceContext context = e.getDragSourceContext();
      //intersection of the users selected action, and the source and target actions
      int myaction = e.getDropAction();
      if (myaction == DnDConstants.ACTION_COPY)
      {
        context.setCursor(DragSource.DefaultCopyDrop);	  
      } 
      else if (myaction == DnDConstants.ACTION_MOVE)
      {
	context.setCursor(DragSource.DefaultMoveDrop);	  	
      }
      else
      {
          System.out.println("Drag action not recognized, myaction == " + myaction);
      }
    }
    
    public void dragOver(DragSourceDragEvent e) 
    {
      DragSourceContext context = e.getDragSourceContext();
      int sa = context.getSourceActions();
      int ua = e.getUserAction();
      int da = e.getDropAction();
      int ta = e.getTargetActions();
      System.out.println("dl dragOver source actions" + sa);
      System.out.println("user action" + ua);
      System.out.println("drop actions" + da);
      System.out.println("target actions" + ta);      
    }
    
    public void dragExit(DragSourceEvent e) 
    {
      System.out.println( "draglabel exit " + e);      
      DragSourceContext context = e.getDragSourceContext();
    }

    
     // for example, press shift during drag to change to
     // a link action
    
    public void dropActionChanged (DragSourceDragEvent e) 
    {
      DragSourceContext context = e.getDragSourceContext();      
      context.setCursor(DragSource.DefaultCopyNoDrop);	  	
    }
    
    ////////////////////////////////////////////////////////////
    // Drop Support Section
    ////////////////////////////////////////////////////////////
    private boolean isDragFlavorSupported(DropTargetDragEvent e) {
      boolean ok=false;
      if (e.isDataFlavorSupported(StringTransferable.plainTextFlavor)) {
	ok=true;
      } else if (e.isDataFlavorSupported(
	StringTransferable.localStringFlavor)) {
	ok=true;
      } else if (e.isDataFlavorSupported(DataFlavor.stringFlavor)) {	  
	ok=true;
      } else if (e.isDataFlavorSupported(DataFlavor.plainTextFlavor)) {
	ok=true;
      }
      return ok;
    }
    
     // Called by drop
     // Checks the flavors and operations
     // @param e the DropTargetDropEvent object
     // @return the chosen DataFlavor or null if none match
     
    private DataFlavor chooseDropFlavor(DropTargetDropEvent e) {
      if (e.isLocalTransfer() == true &&
	e.isDataFlavorSupported(StringTransferable.localStringFlavor)) {
	return StringTransferable.localStringFlavor;
      }
      DataFlavor chosen = null;      
      if (e.isDataFlavorSupported(StringTransferable.plainTextFlavor)) {
	chosen = StringTransferable.plainTextFlavor;
      } else if (e.isDataFlavorSupported(
	StringTransferable.localStringFlavor)) {
	chosen = StringTransferable.localStringFlavor;	
      } else if (e.isDataFlavorSupported(DataFlavor.stringFlavor)) {	  
	chosen = DataFlavor.stringFlavor;
      } else if (e.isDataFlavorSupported(DataFlavor.plainTextFlavor)) {
	chosen = DataFlavor.plainTextFlavor;	
      }
      return chosen;
    }
  
    
     // start "drag under" feedback on component
     // invoke acceptDrag or rejectDrag based on isDragOk
     
    public void dragEnter(DropTargetDragEvent e) 
    {
      System.out.println( "dtlistener dragEnter");    
      System.out.println( "dt enter: accepting " + e.getDropAction());
      e.acceptDrag(e.getDropAction());      
    }

    
     // continue "drag under" feedback on component
     // invoke acceptDrag or rejectDrag based on isDragOk
     
    public void dragOver(DropTargetDragEvent e) 
    {
      System.out.println( "dt over: accepting");
      e.acceptDrag(e.getDropAction());            
    }
    
    public void dropActionChanged(DropTargetDragEvent e) 
    {
      System.out.println( "dt changed: accepting"+e.getDropAction());
      e.acceptDrag(e.getDropAction());            
    }
    
    public void dragExit(DropTargetEvent e) 
    {
      System.out.println( "dtlistener dragExit");
    }

    
     // perform action from getSourceActions on
     // the transferrable
     // invoke acceptDrop or rejectDrop
     // invoke dropComplete
     // if its a local (same JVM) transfer, use StringTransferable.localStringFlavor
     // find a match for the flavor
     // check the operation
     // get the transferable according to the chosen flavor
     // do the transfer
     
    public void drop(DropTargetDropEvent e) 
    {
      System.out.println( "dtlistener drop");
      
      DataFlavor chosen = chooseDropFlavor(e);
      if (chosen == null) {
	System.err.println( "No flavor match found" );
	e.rejectDrop();      	
	return;
      }
      System.err.println( "Chosen data flavor is " + chosen.getMimeType());

      // the actual operation
      int da = e.getDropAction();
      // the actions that the source has specified with DragGestureRecognizer
      int sa = e.getSourceActions();      
      System.out.println( "drop: sourceActions: " + sa);
      System.out.println( "drop: dropAction: " + da);
      
      Object data=null;
      try {
	
	 // the source listener receives this action in dragDropEnd.
	 // if the action is DnDConstants.ACTION_COPY_OR_MOVE then
	 // the source receives MOVE!
	 
	e.acceptDrop(sa);
	// e.acceptDrop(DnDConstants.ACTION_MOVE);
	//e.acceptDrop(DnDConstants.ACTION_COPY);
	//e.acceptDrop(DnDConstants.ACTION_COPY_OR_MOVE); 
  
	data = e.getTransferable().getTransferData(chosen);
	if (data == null)
	  throw new NullPointerException();
      } catch ( Throwable t ) {
	System.err.println( "Couldn't get transfer data: " + t.getMessage());
	t.printStackTrace();
	e.dropComplete(false);  		
	return;
      }
      System.out.println( "Got data: " + data.getClass().getName() );
      
      if (data instanceof String ) 
      {
	String s = (String) data;
        // insert text now...
        System.out.println("Insert text now...");
      } 
      else 
      {
	System.out.println( "drop: rejecting");
	e.dropComplete(false);      	  	
	return;
      }
      
      e.dropComplete(true);      
   }
   */
   public void dragGestureRecognized(DragGestureEvent e) 
    {
        System.out.println(e.getDragAction());
        System.out.println( "kicking off drag");
        // get the label's text and put it inside a Transferable
        
        // if  a selection exists the right mouse button has been released, then
        // set dragReady to true...
        if (dragReady)
        {
            Transferable transferable = new StringSelection( textPane.getSelectedText() );      
            if (transferable != null)
            {
                try 
                {
                    // initial cursor, transferrable, dsource listener
                    e.startDrag(DragSource.DefaultCopyDrop,
                        transferable,
                        this);
                } 
                catch ( InvalidDnDOperationException idoe ) 
                {
                    System.err.println( idoe );
                }
            }
            else
            {
                System.out.println("transferable = null");
            }
        }
    }   
    
    public void dragDropEnd(DragSourceDropEvent e) 
    {
        System.out.println( "dragdropend action " + e.getDropAction() );

        // this is the action selected by the drop target
        if (e.getDropAction() == DnDConstants.ACTION_MOVE)
        {
            // here is where we would clear the selection in the source...
	    //DragLabel.this.setText("");
        }
    }

    
    public void dragEnter(DragSourceDragEvent e) 
    {
      System.out.println( "draglabel enter " + e);
    }
    
    public void dragOver(DragSourceDragEvent e) 
    {
       
    }
    
    public void dragExit(DragSourceEvent e) 
    {
     
    }
     
    public void dropActionChanged (DragSourceDragEvent e) 
    {
     	
    }
    
    ////////////////////////////////////////////////////////////
    // Drop Support Section
    ////////////////////////////////////////////////////////////
 
     // perform action from getSourceActions on
     // the transferrable
     // invoke acceptDrop or rejectDrop
     // invoke dropComplete
     // if its a local (same JVM) transfer, use StringTransferable.localStringFlavor
     // find a match for the flavor
     // check the operation
     // get the transferable according to the chosen flavor
     // do the transfer
     
    public void drop(DropTargetDropEvent e) 
    {
      System.out.println( "dtlistener drop");
      
      // the actual operation
      int da = e.getDropAction();
      // the actions that the source has specified with DragGestureRecognizer
      int sa = e.getSourceActions();      
      System.out.println( "drop: sourceActions: " + sa);
      System.out.println( "drop: dropAction: " + da);
      
      Object data=null;
      try {
	
	 // the source listener receives this action in dragDropEnd.
	 // if the action is DnDConstants.ACTION_COPY_OR_MOVE then
	 // the source receives MOVE!
	 
	e.acceptDrop(sa);
	// e.acceptDrop(DnDConstants.ACTION_MOVE);
	//e.acceptDrop(DnDConstants.ACTION_COPY);
	//e.acceptDrop(DnDConstants.ACTION_COPY_OR_MOVE); 
  
	data = e.getTransferable().getTransferData(DataFlavor.stringFlavor);
        
	if (data == null)
	  throw new NullPointerException();
      } catch ( Throwable t ) {
	System.err.println( "Couldn't get transfer data: " + t.getMessage());
	t.printStackTrace();
	e.dropComplete(false);  		
	return;
      }
      System.out.println( "Got data: " + data.getClass().getName() );
      
      if (data instanceof String ) 
      {
	String s = (String) data;
        // insert text now...
        System.out.println("Insert text now...");
      } 
      else 
      {
	System.out.println( "drop: rejecting");
	e.dropComplete(false);      	  	
	return;
      }
      
      e.dropComplete(true);      
   }
   
   public void dragOver(java.awt.dnd.DropTargetDragEvent p1) {
   }
   
   public void dropActionChanged(java.awt.dnd.DropTargetDragEvent p1) {
   }
   
   public void dragEnter(java.awt.dnd.DropTargetDragEvent p1) {
   }
   
   public void dragExit(java.awt.dnd.DropTargetEvent p1) {
   }
   
   public void mouseReleased(java.awt.event.MouseEvent p1) 
   {
      if (textPane.getSelectedText() != null)
         dragReady = true;
      else
         dragReady = false;
      System.out.println("mousereleased, dragReady = " + dragReady);
   }
   
   public void mouseEntered(java.awt.event.MouseEvent p1) {
   }
   
   public void mouseClicked(java.awt.event.MouseEvent p1) 
   {
      /*
      if (textPane.getSelectedText() != null)
         dragReady = true;
      else
         dragReady = false;
       System.out.println("mouseclicked, dragReady = "+dragReady);
  */
   }
   
   public void mousePressed(java.awt.event.MouseEvent p1) {
   }
   
   public void mouseExited(java.awt.event.MouseEvent p1) {
   }
   
   public int print( Graphics page, PageFormat pageFormat, int pageIndex ) throws PrinterException 
      /****************************************************************
      * Method:
      *   print puts together all the pieces necessary to print a page
      *   of the current DocumentFrame.
      * Inputs:
      *   Graphics page, PageFormat pageFormat, and int pageIndex
      * Outputs:
      *   int status.
      ****************************************************************/
   {
         int status;
         
         Dimension pageDimensions = this.getSize();
         double panelWidth = pageDimensions.width;
         double panelHeight = pageDimensions.height;
         double pageHeight = pageFormat.getImageableHeight();
         double pageWidth = pageFormat.getImageableWidth();

         double scale = pageWidth / panelWidth;
         int totalNumPages = (int)Math.ceil( scale * panelHeight / pageHeight );

         if( pageIndex >= totalNumPages )
         {
            status = Printable.NO_SUCH_PAGE;
         }
         else
         {
            Graphics2D page2D = (Graphics2D)page;
            page2D.translate( pageFormat.getImageableX(), pageFormat.getImageableY() );
            page2D.translate( 0f, -pageIndex * pageHeight );
            page2D.scale( scale, scale );
            this.print( page2D );
            status = Printable.PAGE_EXISTS;
         }
         
         return status;
   }

   public void startPrint()
   { 
     PrinterJob printJob = PrinterJob.getPrinterJob();
     Book book = new Book();

     if ( printJob.printDialog() ) 
     {
        PageFormat documentPageFormat = new PageFormat ();
        documentPageFormat = printJob.pageDialog( documentPageFormat );
        book.append( (JInternalFrame)this, documentPageFormat );    

        try 
        {
           printJob.setPrintable( this );
           printJob.print();
        } 
        catch ( Exception e ) 
        {
           System.out.println( e.getMessage() );
        }
     }
   }
}
