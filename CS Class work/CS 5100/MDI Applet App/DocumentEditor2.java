/**********************************************************************
* Program:
*   Multiple document text editor - assignment 5
* Author:
*   Jeff Hillman
**********************************************************************/
import java.io.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.print.*;
import java.awt.image.*;
import java.awt.dnd.*;
import java.awt.datatransfer.*;
import javax.swing.event.*;
import javax.swing.text.*;
import javax.swing.*;
import java.applet.*;
import javax.swing.filechooser.*;

public class DocumentEditor extends JFrame implements ActionListener
/**********************************************************************
* Class:
*   DocumentEditor creates a JDesktopPane that will hold the internal
*   documents.  It has a menu bar with all the normal selections for
*   a text editor.   
**********************************************************************/   
{
   private Container container;
   private StyledEditorKit editorKit;
   private DefaultStyledDocument document;
   private FileInputStream fileInputStream;
   private FileOutputStream fileOutputStream;
   private JDesktopPane documentPile;
   private Hashtable actions;
   private Action [] actionsArray;
   private JMenuBar menuBar;
   private JMenu fileMenu;
   private JMenuItem newFile;
   private JMenuItem open;
   private JMenuItem save;
   private JMenuItem saveAs;
   private JMenuItem close;
   private JMenuItem print;
   private JMenuItem exit;
   private JMenu editMenu;
   private Action cut;
   private Action copy;
   private Action paste;
   private Action selectAll;
   private JMenuItem find;
   private JMenuItem replace;
   private JPopupMenu popupEditMenu;
   private Action popupCut;
   private Action popupCopy;
   private Action popupPaste;
   private Action popupSelectAll;
   private JMenuItem popupFind;
   private JMenuItem popupReplace;
   private JMenu windowMenu;
   private JPanel fontHolder;
   private JComboBox fonts;
   private JButton fontButtonOne;
   private JButton fontButtonTwo;
   private JButton fontButtonThree;
   private JButton fontButtonFour;
   private JButton fontButtonFive;
   private Properties properties;
   private String relativePath;
   private int documentNumber;
   private int newDocumentNumber;
   private int currentDocumentNumber;
   private int documentsOpen;
   private boolean popupVisible;
   private PopupListener popupListener;
   private Vector openWindows;
   private DocumentFrame currentDocumentFrame;
   private JFileChooser fileChooser;
   private boolean runningAsApplet;
   
   public DocumentEditor( boolean runningAsApplet )
   /*******************************************************************
   * Method:
   *   DocumentEditor constructor
   * Inputs:
   *   none.
   * Outputs:
   *   none.
   *******************************************************************/
   {
   	  int i;
   	  int width = 600;
   	  int height = 700;
   	  
   	  this.runningAsApplet = runningAsApplet;
   	  
      setSize( width, height ); 

   	  relativePath = "";
   	  documentNumber = 0;
   	  newDocumentNumber = 1;
   	  documentsOpen = 0;
   	  popupVisible = false;
   	  
      try
      {     
         UIManager.setLookAndFeel( UIManager.getSystemLookAndFeelClassName() );
      }
      catch ( Exception e )
      {
         System.out.println( e.getMessage() );      
      }

      container = getContentPane();
   
      fileMenu = new JMenu( "File" );
      fileMenu.setMnemonic( KeyEvent.VK_F );
      
      newFile = new JMenuItem( "New", KeyEvent.VK_O );
      newFile.setMnemonic( KeyEvent.VK_N );
      newFile.setAccelerator( KeyStroke.getKeyStroke( KeyEvent.VK_N, ActionEvent.CTRL_MASK ) );
      newFile.addActionListener( this );
      open = new JMenuItem( "Open", KeyEvent.VK_O );
      open.setMnemonic( KeyEvent.VK_O );
      open.setAccelerator( KeyStroke.getKeyStroke( KeyEvent.VK_O, ActionEvent.CTRL_MASK ) );
      open.addActionListener( this );
      save = new JMenuItem( "Save" );
      save.setMnemonic( KeyEvent.VK_S );
      save.setAccelerator( KeyStroke.getKeyStroke( KeyEvent.VK_S, ActionEvent.CTRL_MASK ) );
      save.addActionListener( this );
      save.setEnabled( false );
      saveAs = new JMenuItem( "Save As..." );
      saveAs.addActionListener( this );
      saveAs.setEnabled( false );
      close = new JMenuItem( "Close" );
      close.addActionListener( this );
      close.setEnabled( false );
      print = new JMenuItem( "Print" );
      print.setMnemonic( KeyEvent.VK_P );
      print.setAccelerator( KeyStroke.getKeyStroke( KeyEvent.VK_P, ActionEvent.CTRL_MASK ) );
      print.addActionListener( this );
      print.setEnabled( false );
      exit = new JMenuItem( "Exit" );
      exit.addActionListener( this );
      
      fileMenu.add( newFile );
      fileMenu.add( open );
      fileMenu.add( save );
      fileMenu.add( saveAs );
      fileMenu.add( close );
      fileMenu.add( print );
      fileMenu.add( exit );
      
      editMenu = new JMenu( "Edit" );
      editMenu.setMnemonic( KeyEvent.VK_E );
      
      JTextPane textPane = new JTextPane();
      
      actions = new Hashtable();
      actionsArray = textPane.getActions();
      
      for ( i = 0; i < actionsArray.length; i++ )
      {
         actions.put( actionsArray[ i ].getValue( Action.NAME ), actionsArray[ i ] );
      }
      
      cut = (Action)( actions.get( DefaultEditorKit.cutAction ) );
      cut.putValue(Action.NAME, "Cut");
      cut.putValue( Action.ACCELERATOR_KEY, 
                    KeyStroke.getKeyStroke( KeyEvent.VK_X, ActionEvent.CTRL_MASK ) );
      cut.setEnabled( false );
      copy = (Action)( actions.get( DefaultEditorKit.copyAction ) );
      copy.putValue( Action.NAME, "Copy" );
      copy.putValue( Action.ACCELERATOR_KEY, 
                     KeyStroke.getKeyStroke( KeyEvent.VK_C, ActionEvent.CTRL_MASK ) );
      copy.setEnabled( false );
      paste = (Action)( actions.get( DefaultEditorKit.pasteAction ) );
      paste.putValue( Action.NAME, "Paste" );
      paste.putValue( Action.ACCELERATOR_KEY, 
                      KeyStroke.getKeyStroke( KeyEvent.VK_V, ActionEvent.CTRL_MASK ) );
      paste.setEnabled( false );
      selectAll = (Action)( actions.get( DefaultEditorKit.selectAllAction ) );
      selectAll.putValue( Action.NAME, "Select All" );
      selectAll.putValue( Action.ACCELERATOR_KEY, 
                          KeyStroke.getKeyStroke( KeyEvent.VK_A, ActionEvent.CTRL_MASK ) );
      selectAll.setEnabled( false );
      find = new JMenuItem( "Find" );
      find.setAccelerator( KeyStroke.getKeyStroke( KeyEvent.VK_F, ActionEvent.CTRL_MASK ) );
      find.addActionListener( this );
      find.setEnabled( false );
      replace = new JMenuItem( "Replace" );
      replace.setAccelerator( KeyStroke.getKeyStroke( KeyEvent.VK_H, ActionEvent.CTRL_MASK ) );
      replace.addActionListener( this );
      replace.setEnabled( false );

      editMenu.add( cut );
      editMenu.add( copy );
      editMenu.add( paste );
      editMenu.add( selectAll );
      editMenu.add( find );
      editMenu.add( replace );
      
      popupEditMenu = new JPopupMenu();

      popupCut = (Action)( actions.get( DefaultEditorKit.cutAction ) );
      popupCut.putValue( Action.NAME, "Cut");
      popupCopy = (Action)( actions.get( DefaultEditorKit.copyAction ) );
      popupCopy.putValue( Action.NAME, "Copy" );
      popupPaste = (Action)( actions.get( DefaultEditorKit.pasteAction ) );
      popupPaste.putValue(Action.NAME, "Paste");
      popupSelectAll = (Action)( actions.get( DefaultEditorKit.selectAllAction ) );
      popupSelectAll.putValue( Action.NAME, "Select All" );
      popupFind = new JMenuItem( "Find" );
      popupFind.setAccelerator( KeyStroke.getKeyStroke( KeyEvent.VK_F, ActionEvent.CTRL_MASK ) );
      popupFind.addActionListener( this );
      popupFind.setEnabled( false );
      popupReplace = new JMenuItem( "Replace" );
      popupReplace.setAccelerator( KeyStroke.getKeyStroke( KeyEvent.VK_H, ActionEvent.CTRL_MASK ) );
      popupReplace.addActionListener( this );
      popupReplace.setEnabled( false );

      popupEditMenu.add( popupCut );
      popupEditMenu.add( popupCopy );
      popupEditMenu.add( popupPaste );
      popupEditMenu.add( popupSelectAll );
      popupEditMenu.add( popupFind );
      popupEditMenu.add( popupReplace );
      
      windowMenu = new JMenu( "Window" );
      windowMenu.setMnemonic( KeyEvent.VK_W );

      menuBar = new JMenuBar();
      menuBar.add( fileMenu );
      menuBar.add( editMenu );
      menuBar.add( windowMenu );
      
      fontButtonOne = new JButton();
      fontButtonOne.addActionListener( 
         new StyledEditorKit.FontFamilyAction( "Courier","Courier" ) );
      fontButtonTwo = new JButton();
      fontButtonTwo.addActionListener( 
         new StyledEditorKit.FontFamilyAction( "Helvetica","Helvetica" ) );
      fontButtonThree = new JButton();
      fontButtonThree.addActionListener( 
         new StyledEditorKit.FontFamilyAction( "Verdana","Verdana" ) );
      fontButtonFour = new JButton();
      fontButtonFour.addActionListener( 
         new StyledEditorKit.FontFamilyAction( "Serif","Serif" ) );
      fontButtonFive = new JButton();
      fontButtonFive.addActionListener( 
         new StyledEditorKit.FontFamilyAction( "Tahoma","Tahoma" ) );

      String [] fontList = { "Courier", "Helvetica", "Verdana", "Serif", "Tahoma" };
      
      fonts = new JComboBox( fontList );
      fonts.addActionListener( this );
      
      fontHolder = new JPanel( new FlowLayout( FlowLayout.LEFT, 0, 0 ) );
      
      fontHolder.add( fonts );
      
      menuBar.add( fontHolder );

      setJMenuBar( menuBar );
      
      popupListener = new PopupListener();
      
      addMouseListener( popupListener );
      
      documentPile = new JDesktopPane();
      
      documentPile.setBackground( Color.lightGray );
      
      documentPile.addMouseListener( popupListener );
      
      container.add( documentPile );
      
      editorKit = new StyledEditorKit();
      openWindows = new Vector();

      if ( runningAsApplet == false )
      {
         properties = System.getProperties();
      }

      addWindowListener( new WindowAdapter()
      {
         public void windowClosing( WindowEvent e ) 
         {
            actionPerformed( new ActionEvent( exit, ActionEvent.ACTION_PERFORMED, null ) );
         }
      });
      
      Toolkit toolkit = Toolkit.getDefaultToolkit(); 
      Dimension dimension = toolkit.getScreenSize();
      
      setLocation ( dimension.width/2 - width/2, dimension.height/2 - height/2 ); 

      setTitle( "Document Editor - by Jeff Hillman" );
      setVisible( true );   	  
   }
   
   public void actionPerformed( ActionEvent event )
   /*******************************************************************
   * Method:
   *   actionPerformed takes care of all the events coming from the 
   *   menus and popupMenu, as well as some action keys.
   * Inputs:
   *   ActionEvent event.
   * Outputs:
   *   none
   *******************************************************************/
   {
      Object source = event.getSource();
      String actionCommand = event.getActionCommand();
      int returnValue;
      File file;
      String fileName;
      FileInputStream fileInputStream;
      ObjectInputStream objectInputStream;
      StyledDocument styledDocument;
      JMenuItem fileNameMenuItem;
      
      if ( documentsOpen > 0 )
      {
         currentDocumentFrame = (DocumentFrame)documentPile.getSelectedFrame();
      }
      else
      {
      	 currentDocumentFrame = new DocumentFrame( null, null );
      }
      
      if ( runningAsApplet )
      {
      	 fileChooser = new JFileChooser();
      }
      else
      {
         if ( relativePath.length() == 0 )
         {
            if ( properties.contains( "Shell" ) )
            {
               relativePath = properties.getProperty( "currentDir" );
            }
            else
            {
               relativePath = properties.getProperty( "user.dir" );
            }
         }
   
         fileChooser = new JFileChooser( relativePath );
      }
      

      if ( source == newFile )
      {
      	 currentDocumentFrame = new DocumentFrame( null, null );

         currentDocumentFrame.getDocument().setStyledDocument( new DefaultStyledDocument() );

         currentDocumentFrame.addMouseListener( popupListener );
         
         documentPile.add( currentDocumentFrame );
         
 	 	 try
 	 	 {
            currentDocumentFrame.setSelected( true );
         }
         catch ( java.beans.PropertyVetoException e )
         {
            System.out.println( e.getMessage() );	
         }
         
         openWindows.add( currentDocumentFrame );

         updateWindowTitleMenu();
         
         ++newDocumentNumber;
         ++documentsOpen;
         
         currentDocumentFrame.getDocument().requestFocus();
      }

      if ( source == open )
      {
         returnValue = fileChooser.showOpenDialog( this );

         if ( returnValue == JFileChooser.APPROVE_OPTION ) 
         {
            file = fileChooser.getSelectedFile();

            try
            {
               fileInputStream = new FileInputStream( file );
               document = new DefaultStyledDocument();

               editorKit.read( fileInputStream, document, 0 );

           	   currentDocumentFrame = new DocumentFrame( 
           	      new File( fileChooser.getCurrentDirectory(), 
           	                fileChooser.getSelectedFile().getName() ), null );

               currentDocumentFrame.getDocument().setStyledDocument( document );
               
               documentPile.add( currentDocumentFrame );
               
          	   try
 	 	       {
                  currentDocumentFrame.setSelected( true );
               }
               catch ( java.beans.PropertyVetoException e )
               {
                  System.out.println( e.getMessage() );	
               }
               
               openWindows.add( currentDocumentFrame );
               
               updateWindowTitleMenu();
            }
            catch ( Exception e )
            {
               System.out.println( e.getMessage() );
            }

            ++documentsOpen;      
            currentDocumentFrame.getDocument().requestFocus();
         } 
      }
      
      if ( source == save )
      {
         if ( currentDocumentFrame.getFile() != null )
         {
            try
            {
               fileOutputStream = new FileOutputStream( currentDocumentFrame.getFile() );
               editorKit.write( fileOutputStream, 
                                currentDocumentFrame.getDocument().getStyledDocument(), 0, 
                                currentDocumentFrame.getDocument().getStyledDocument().getLength() );
            }
            catch( Exception e )
            {
               System.out.println( e.getMessage() );
            }
      
            currentDocumentFrame.setTitle( currentDocumentFrame.getFile().getName() );
            currentDocumentFrame.setModified( false );
            updateWindowTitleMenu();
         }
         else
         {
            this.actionPerformed( new ActionEvent( saveAs, ActionEvent.ACTION_PERFORMED, null ) );	
         }
      }

      if ( source == saveAs )
      {
         fileChooser.setSelectedFile( currentDocumentFrame.getFile() );
         returnValue = fileChooser.showDialog( this, "Save As..." );

         if ( returnValue == JFileChooser.APPROVE_OPTION ) 
         {
            file = fileChooser.getSelectedFile();
            file = new File( fileChooser.getCurrentDirectory(), file.getName() );
            currentDocumentFrame.setFile( file );
            documentPile.getSelectedFrame().setTitle(  file.getName() );

            try
            {
               fileOutputStream = new FileOutputStream( file );
               editorKit.write( fileOutputStream, 
                                currentDocumentFrame.getDocument().getStyledDocument(), 0, 
                                currentDocumentFrame.getDocument().getStyledDocument().getLength() );
            }
            catch( Exception e )
            {
               System.out.println( e.getMessage() );
            }

            updateWindowTitleMenu();
            currentDocumentFrame.setModified( false );
         }
      }
      
      if ( source == close && documentsOpen > 0 )
      {
         new ClosingDialog();
      }
      
      if ( source == print )
      {
         ( (DnDTextPane)currentDocumentFrame.getDocument() ).startPrint();
      }
      
      if ( source == exit )
      {
         while ( openWindows.isEmpty() == false )
      	 {
            try
	        {
      	       ( (DocumentFrame)openWindows.elementAt( 0 ) ).setClosed( true );
            }
            catch ( java.beans.PropertyVetoException e )
            {
               System.out.println( e.getMessage() );	
            }
      	 }
      	 
      	 System.exit( 0 );
      }
      
      if ( source == find || source == popupFind )
      {
      	 if ( currentDocumentFrame.getDocument().getSelectedText() != null )
      	 {
      	    new FindDialog( currentDocumentFrame.getDocument().getSelectedText() );	
      	 }
      	 else
      	 {
      	    new FindDialog();
      	 }
      }
      
      if ( source == replace || source == popupReplace )
      {
   	     new ReplaceDialog();
      }
      
      if ( source == fonts && documentsOpen > 0 )
      {
      	 boolean textSelected = false;
      	 int caretPosition = currentDocumentFrame.getDocument().getCaretPosition();
      	 
      	 if ( currentDocumentFrame.getDocument().getSelectedText() != null )
      	 {
      	    textSelected = true;	
      	 }
      	
      	 switch ( fonts.getSelectedIndex() )
      	 {
      	    case 0:
               if ( !textSelected )
               {
                  currentDocumentFrame.getDocument().selectAll();
               }

               fontButtonOne.doClick();
      	       break;	
      	    case 1:
               if ( !textSelected )
               {
                  currentDocumentFrame.getDocument().selectAll();
               }

               fontButtonTwo.doClick();
      	       break;	
      	    case 2:
               if ( !textSelected )
               {
                  currentDocumentFrame.getDocument().selectAll();
               }

               fontButtonThree.doClick();
      	       break;	
      	    case 3:
               if ( !textSelected )
               {
                  currentDocumentFrame.getDocument().selectAll();
               }

               fontButtonFour.doClick();
      	       break;	
      	    case 4:
               if ( !textSelected )
               {
                  currentDocumentFrame.getDocument().selectAll();
               }

               fontButtonFive.doClick();
      	       break;	
      	 }
      	 
      	 currentDocumentFrame.getDocument().setCaretPosition( caretPosition );
      }

      if ( documentsOpen > 0 )
      {
      	 save.setEnabled( true );
      	 saveAs.setEnabled( true );
      	 print.setEnabled( true );
      	 close.setEnabled( true );
      	 cut.setEnabled( true );
      	 copy.setEnabled( true );
      	 paste.setEnabled( true );
      	 selectAll.setEnabled( true );
      	 find.setEnabled( true );
      	 replace.setEnabled( true );
      	 popupCut.setEnabled( true );
      	 popupCopy.setEnabled( true );
      	 popupPaste.setEnabled( true );
      	 popupSelectAll.setEnabled( true );
      	 popupFind.setEnabled( true );
      	 popupReplace.setEnabled( true );
      }
      else
      {
      	 save.setEnabled( false );
      	 saveAs.setEnabled( false );
      	 print.setEnabled( false );
      	 close.setEnabled( false );
      	 cut.setEnabled( false );
      	 copy.setEnabled( false );
      	 paste.setEnabled( false );
      	 selectAll.setEnabled( false );
      	 find.setEnabled( false );
      	 replace.setEnabled( false );
      	 popupCut.setEnabled( false );
      	 popupCopy.setEnabled( false );
      	 popupPaste.setEnabled( false );
      	 popupSelectAll.setEnabled( false );
      	 popupFind.setEnabled( false );
      	 popupReplace.setEnabled( false );
      }
   }
   
   private void updateWindowTitleMenu()
   /*******************************************************************
   * Method:
   *   updateWindowTitleMenu is called when a change has been made to
   *   the number of documents open, or when a document's name is 
   *   changed.  The current list of documents are placed in the menu
   *   as AbstractActions.
   * Inputs:
   *   none.
   * Outputs:
   *   none.
   *******************************************************************/
   {
   	  JMenuItem fileNameMenuItem;

   	  windowMenu.removeAll();
   	  
   	  for ( int i = 0; i < openWindows.size(); i++ )
   	  {
         windowMenu.add( new MenuAction( (DocumentFrame)openWindows.elementAt( i ) ) );
   	  }
   }
   
   private class MenuAction extends AbstractAction
   /*******************************************************************
   * Class:
   *   MenuAction opens the window with the name held by the action.
   *******************************************************************/   
   {
   	  private DocumentFrame frameToDisplay;
   	
   	  public MenuAction( DocumentFrame frame )
      /****************************************************************
      * Method:
      *   MenuAction constructor.
      * Inputs:
      *   DocumentFrame frame.
      * Outputs:
      *   none.
      ****************************************************************/
   	  {
   	  	 super( frame.getTitle() );
   	  	 
   	  	 frameToDisplay = frame;
   	  	 
   	  	 {
   	  	    putValue( "Name", frame.getTitle() );
   	  	    putValue( "Frame", frame );	
   	  	 }
   	  }
   	  
   	  public void actionPerformed( ActionEvent event )
      /****************************************************************
      * Method:
      *   actionPerformed places frameToDisplay at the front of the
      *   desktop, and attempts to select it.
      * Inputs:
      *   ActionEvent event.
      * Outputs:
      *   none.
      ****************************************************************/
   	  {
   	  	 ( (JInternalFrame)frameToDisplay ).moveToFront();

 	 	 try
 	 	 {
            ( (DocumentFrame)frameToDisplay ).setSelected( true );           
            ( (DocumentFrame)frameToDisplay ).getDocument().requestFocus();
         }
         catch ( java.beans.PropertyVetoException e )
         {
            System.out.println( e.getMessage() );	
         }
   	  }
   }

   private class PopupListener extends MouseAdapter
   /*******************************************************************
   * Class:
   *   Popuplistener responds to mouse events that are to pop up the 
   *   edit menu.
   *******************************************************************/   
   { 
   	  public void mousePressed( MouseEvent event )
      {
         showPopup( event );      	 	
      }
      	
      public void mouseReleased( MouseEvent event )
      {
         showPopup( event );      	 	
      }
      	
      public void mouseClicked( MouseEvent event )
      {
         showPopup( event );      	 	
      }
      	
      public void showPopup( MouseEvent event ) 
      /****************************************************************
      * Method:
      *   showPopup determines whether the mouse event just performed
      *   is the popup trigger, and, if so, displays the popup menu.
      * Inputs:
      *   MouseEvent event.
      * Outputs:
      *   none.
      ****************************************************************/
      {
         if ( event.isPopupTrigger() )
         {
            if ( popupVisible )
            {
               popupVisible = false;
               popupEditMenu.setVisible( false );	
            }
            else
            {
               popupVisible = true;
               popupEditMenu.show( event.getComponent(), event.getX(), event.getY() );	
            }
         }
      }
   }   
   
   private class ClosingDialog extends JDialog implements ActionListener
   /*******************************************************************
   * Class:
   *   ClosingDialog displays a list of the open documents, and the
   *   user can select the document he wishes to close.
   *******************************************************************/   
   {
   	  private JLabel lineOne;
   	  private JLabel lineTwo;
   	  private JList windowList;
   	  private JScrollPane scrollPane;
   	  private JCheckBox selectAll;
   	  private JButton okay;
   	  private JButton cancel;
   	  private Container container;
   	  private JPanel buttonHolder;
   	  private GridBagLayout gridBag;
   	  private GridBagConstraints constraints;
   	  
   	  public ClosingDialog()
      /****************************************************************
      * Method:
      *   ClosingDialog constructor.
      * Inputs:
      *   none.
      * Outputs:
      *   none.
      ****************************************************************/
   	  {
   	  	 int width = 210;
   	  	 int height = 240;
   	  	 
   	  	 setResizable( false );
   	  	 
   	  	 gridBag = new GridBagLayout();
   	  	 constraints = new GridBagConstraints();
   	  	 
   	  	 container = getContentPane();
   	  	 container.setLayout( gridBag );
   	  	 
   	  	 lineOne = new JLabel( "Select the documents to", JLabel.LEFT );
   	  	 
   	  	 constraints.gridx = 0;
   	  	 constraints.gridy = 0;
   	  	 
   	  	 gridBag.setConstraints( lineOne, constraints );
   	  	 
   	  	 container.add( lineOne );
   	  	 
   	  	 lineTwo = new JLabel( "close, then click OK.", JLabel.LEFT );
   	  	 
   	  	 constraints.gridx = 0;
   	  	 constraints.gridy = 1;
   	  	 
   	  	 gridBag.setConstraints( lineTwo, constraints );
   	  	 
   	  	 container.add( lineTwo );
   	  	 
   	  	 windowList = new JList( openWindows );
   	  	 
   	  	 WindowListRenderer renderer = new WindowListRenderer();
   	  	 
   	  	 windowList.setCellRenderer( renderer );
   	  	 
   	  	 scrollPane = new JScrollPane( windowList, 
   	  	                               JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, 
   	  	                               JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED );
   	  	 
   	  	 scrollPane.setPreferredSize( new Dimension( 150, 100 ) );
   	  	 
   	  	 constraints.gridx = 0;
   	  	 constraints.gridy = 2;
   	  	 constraints.insets = new Insets( 2, 2, 2, 2 );
   	  	 
   	  	 gridBag.setConstraints( scrollPane, constraints );
   	  	 
   	  	 container.add( scrollPane );
   	  	 
   	  	 selectAll = new JCheckBox( "Select All" );
   	  	 selectAll.addActionListener( this );
   	  	 
   	  	 constraints.gridx = 0;
   	  	 constraints.gridy = 3;
   	  	 
   	  	 gridBag.setConstraints( selectAll, constraints );
   	  	 
   	  	 container.add( selectAll );
   	  	 
   	  	 buttonHolder = new JPanel( new GridLayout( 1, 2, 5, 5 ) );
   	  	 
   	  	 okay = new JButton( "OK" );
   	  	 okay.addActionListener( this );
   	  	 
   	  	 cancel = new JButton( "Cancel" );
   	  	 cancel.addActionListener( this );
   	  	 
   	  	 buttonHolder.add( okay );
   	  	 buttonHolder.add( cancel );
   	  	 
   	  	 constraints.gridx = 0;
   	  	 constraints.gridy = 4;
   	  	 
   	  	 gridBag.setConstraints( buttonHolder, constraints );
   	  	 
   	  	 container.add( buttonHolder );
   	  	    	  	 
         setSize( width, height );
         
         Toolkit toolkit = Toolkit.getDefaultToolkit(); 
         Dimension dimension = toolkit.getScreenSize(); 
      
         setLocation ( dimension.width/2 - width/2, dimension.height/2 - height/2 ); 
      
         setTitle( "Close" );
         
         setVisible( true );   	  
   	  }
   	  
   	  public void actionPerformed( ActionEvent event )
      /****************************************************************
      * Method:
      *   actionPerformed takes care of the actions performed on the 
      *   ClosingDialog.
      * Inputs:
      *   ActionEvent event.
      * Outputs:
      *   none.
      ****************************************************************/
   	  {
   	  	 Object source = event.getSource();
   	  	 Object [] selectedWindows;
   	  	 int i;
   	  	 
   	  	 if ( source == selectAll )
   	  	 {
   	  	 	if ( selectAll.isSelected() == false )
   	  	 	{
   	  	 	   windowList.removeSelectionInterval( 0, documentsOpen - 1 );
   	  	    }
   	  	    else
   	  	    {
   	  	 	   windowList.setSelectionInterval( 0, documentsOpen - 1 );
   	  	    }
   	  	 }
   	  	 
   	  	 if ( source == cancel )
   	  	 {
   	  	    dispose();	
   	  	 }
   	  	 
   	  	 if ( source == okay )
   	  	 {
   	  	 	selectedWindows = windowList.getSelectedValues();
   	  	 	
   	  	 	for ( i = 0; i < selectedWindows.length; i++ )
   	  	 	{
               try
	           {
      	          ( (DocumentFrame)selectedWindows[ i ] ).setClosed( true );
               }
               catch ( java.beans.PropertyVetoException e )
               {
                  System.out.println( e.getMessage() );	
               }
   	  	 	}

   	  	    dispose();	
   	  	 }
   	  }
   }
        
   private class WindowListRenderer extends JLabel implements ListCellRenderer 
   /*******************************************************************
   * Class:
   *   WindowListRenderer allows the DocumentFrames to be displayed
   *   in a understandable manner in a JList.
   *******************************************************************/   
   {
      public WindowListRenderer() 
      /****************************************************************
      * Method:
      *   WindowListRenderer constructor.
      * Inputs:
      *   none.
      * Outputs:
      *   none.
      ****************************************************************/
      {
        setOpaque(true);
        setHorizontalAlignment(LEFT);
      }
      
      public Component getListCellRendererComponent( JList list, Object value, int index,
                                                     boolean isSelected, boolean cellHasFocus )
      /****************************************************************
      * Method:
      *   getListCellRendererComponent returns the component that is
      *   selected in the JList.
      * Inputs:
      *   JList list, Object value, int index, boolean isSelected, and 
      *   boolean cellHasFocus
      * Outputs:
      *   Component this.
      ****************************************************************/
      {
         if (isSelected) 
         {
            setBackground(list.getSelectionBackground());
            setForeground(list.getSelectionForeground());
         }
         else
         {
            setBackground(list.getBackground());
            setForeground(list.getForeground());
         }

         DocumentFrame frame = (DocumentFrame)value;
         setText( frame.getTitle() );
         return this;
      }
   }
   
   public class FindDialog extends JDialog implements ActionListener
   /*******************************************************************
   * Class:
   *   FindDialog is the typical find utility found in most text
   *   editors.
   *******************************************************************/   
   {
   	  private JLabel findWhat;
   	  private JTextPane document;
   	  private JScrollPane scrollPane;
   	  private JTextField findString;
   	  private JButton find;
   	  private JButton cancel;
   	  private JCheckBox matchCase;
   	  private Container container;
   	  private JPanel buttonHolder;
   	  private GridBagLayout gridBag;
   	  private GridBagConstraints constraints;
      private int lastTextPosition;
      private int newlinesFound;
   	  
   	  public FindDialog()
      /****************************************************************
      * Method:
      *   FindDialog constructor.
      * Inputs:
      *   none.
      * Outputs:
      *   none.
      ****************************************************************/
   	  {
   	  	 int width = 280;
   	  	 int height = 120;
   	  	 
   	  	 setResizable( false );
   	  	 
   	  	 gridBag = new GridBagLayout();
   	  	 constraints = new GridBagConstraints();
   	  	 
   	  	 document = currentDocumentFrame.getDocument();
   	  	 lastTextPosition = document.getCaretPosition();
         newlinesFound = 0;
   	  	 
         document.requestFocus();

   	  	 container = getContentPane();
   	  	 container.setLayout( gridBag );
   	  	 
   	  	 findWhat = new JLabel( "Find: " );
   	  	 
   	  	 constraints.gridx = 0;
   	  	 constraints.gridy = 0;
   	  	 
   	  	 gridBag.setConstraints( findWhat, constraints );
   	  	 
   	  	 container.add( findWhat );
   	  	 
         findString = new JTextField( 12 );

   	  	 constraints.gridx = 1;
   	  	 constraints.gridy = 0;
   	  	 
   	  	 gridBag.setConstraints( findString, constraints );
   	  	 
   	  	 container.add( findString );
   	  	 
   	  	 buttonHolder = new JPanel( new GridLayout( 2, 1, 5, 5 ) );
   	  	 
   	  	 find = new JButton( "Find Next" );
   	  	 find.addActionListener( this );
   	  	 
         cancel = new JButton( "Cancel" );
         cancel.addActionListener( this );
         
         buttonHolder.add( find );
         buttonHolder.add( cancel );

   	  	 constraints.gridx = 2;
   	  	 constraints.gridy = 0;
   	  	 constraints.gridheight = 2;
   	  	 constraints.insets = new Insets( 0, 10, 0, 0 );
   	  	 
   	  	 gridBag.setConstraints( buttonHolder, constraints );
   	  	 
   	  	 container.add( buttonHolder );
   	  	 
         matchCase = new JCheckBox( "Match Case" );
         
         constraints.gridx = 1;
         constraints.gridy = 1;
   	  	 constraints.gridheight = 1;
   	  	 constraints.insets = new Insets( 0, 0, 0, 0 );
            	  	 
   	  	 gridBag.setConstraints( matchCase, constraints );
   	  	 
   	  	 container.add( matchCase );
   	  	 
         setSize( width, height );
         
         Toolkit toolkit = Toolkit.getDefaultToolkit(); 
         Dimension dimension = toolkit.getScreenSize(); 
      
         setLocation ( dimension.width/2 - width/2, dimension.height/2 - height/2 ); 
      
         setTitle( "Find" );
         
         setVisible( true );   	  
   	  }
   	  
   	  public FindDialog( String stringToFind )
      /****************************************************************
      * Method:
      *   FindDialog constructor.
      * Inputs:
      *   String stringToFind.
      * Outputs:
      *   none.
      ****************************************************************/
   	  {
   	  	 this();
   	  	 
         findString.setText( stringToFind );
   	  }
   	  
   	  public void actionPerformed( ActionEvent event )
      /****************************************************************
      * Method:
      *   actionPerformed takes care of the events performed on the
      *   FindDialog.
      * Inputs:
      *   ActionEvent event.
      * Outputs:
      *   none.
      ****************************************************************/
   	  {
   	  	 Object source = event.getSource();
   	  	 boolean matchFound = false;
   	  	 String textToFind = findString.getText();
   	  	 String searchString = document.getText();
   	  	 int location;
   	  	 int response;
   	  	 int i;
   	  	   	  	 
         if ( matchCase.isSelected() == false )
         {
            searchString = searchString.toUpperCase();	
            textToFind = textToFind.toUpperCase();	
         }
         
   	  	 if ( source == cancel )
   	  	 {
   	  	    dispose();	
   	  	 }
   	  	 
   	  	 if ( source == find )
   	  	 {
            location = searchString.indexOf( textToFind, lastTextPosition );
            
            if ( location != -1 )
            {
               document.setSelectionStart( location );
               document.setSelectionEnd( location + textToFind.length() );
               matchFound = true;
               
               if ( document.getSelectedText().equalsIgnoreCase( textToFind ) == false )
               {
                  for ( i = lastTextPosition; i <= location; i++ )
                  {
                     if ( new StringBuffer( searchString ).charAt( i ) == '\n' )
                     {
          	            ++newlinesFound;
                     }
                  }
      
                  document.setSelectionStart( location - newlinesFound );
                  document.setSelectionEnd( location + textToFind.length() - newlinesFound );
               }
                  
               lastTextPosition = location + 1;
            }
            
            if ( matchFound == false )
            {
           	   response = JOptionPane.showConfirmDialog( this,
         	                 "Continue search from beginning?", 
         	                 "End of file found",
                             JOptionPane.YES_NO_OPTION );
                        
               if ( response == JOptionPane.YES_OPTION )
               {                    
                  document.setCaretPosition( 0 );
              	  lastTextPosition = 0;
                  newlinesFound = 0;
                  this.actionPerformed( 
                     new ActionEvent( find, ActionEvent.ACTION_PERFORMED, null ) );
               }
               else
               {
               	  dispose();
               }
            }
   	  	 }
   	  }
   }   

   public class ReplaceDialog extends JDialog implements ActionListener
   /*******************************************************************
   * Class:
   *   ReplaceDialog is the typical search and replace utility found
   *   in most text editors.
   *******************************************************************/   
   {
   	  private JLabel findWhat;
   	  private JLabel replaceWith;
   	  private JLabel numReplacedLabel;
   	  private JScrollPane scrollPane;
   	  private JTextField findString;
   	  private JTextField replaceString;
   	  private JButton find;
   	  private JButton replace;
   	  private JButton replaceAll;
   	  private JButton cancel;
   	  private JCheckBox matchCase;
   	  private Container container;
   	  private JPanel buttonHolder;
   	  private GridBagLayout gridBag;
   	  private GridBagConstraints constraints;
   	  private JTextPane document;
   	  private int totalReplaced;
      private int lastTextPosition;
      private boolean replacingAll;
      private int newlinesFound;
      
   	  public ReplaceDialog()
      /****************************************************************
      * Method:
      *   ReplaceDialog constructor.
      * Inputs:
      *   none.
      * Outputs:
      *   none.
      ****************************************************************/
   	  {
   	  	 int width = 350;
   	  	 int height = 175;
   	  	 
   	  	 setResizable( false );
   	  	 
   	  	 totalReplaced = 0;
   	  	 newlinesFound = 0;
   	  	 replacingAll = false;
   	  	 
   	  	 document = currentDocumentFrame.getDocument();
   	  	 lastTextPosition = document.getCaretPosition();
   	  	 
         document.requestFocus();

   	  	 gridBag = new GridBagLayout();
   	  	 constraints = new GridBagConstraints();
   	  	 
   	  	 container = getContentPane();
   	  	 container.setLayout( gridBag );
   	  	 
   	  	 findWhat = new JLabel( "Search For: " );
   	  	 
   	  	 constraints.gridx = 0;
   	  	 constraints.gridy = 0;
   	  	 constraints.insets = new Insets( 5, 0, 0, 0 );
   	  	 
   	  	 gridBag.setConstraints( findWhat, constraints );
   	  	 
   	  	 container.add( findWhat );
   	  	 
         findString = new JTextField( 12 );

   	  	 constraints.gridx = 1;
   	  	 constraints.gridy = 0;
   	  	 
   	  	 gridBag.setConstraints( findString, constraints );
   	  	 
   	  	 container.add( findString );
   	  	 
   	  	 replaceWith = new JLabel( "Replace With: " );
   	  	 
   	  	 constraints.gridx = 0;
   	  	 constraints.gridy = 1;
   	  	 
   	  	 gridBag.setConstraints( replaceWith, constraints );
   	  	 
   	  	 container.add( replaceWith );
   	  	 
         replaceString = new JTextField( 12 );

   	  	 constraints.gridx = 1;
   	  	 constraints.gridy = 1;
   	  	 
   	  	 gridBag.setConstraints( replaceString, constraints );
   	  	 
   	  	 container.add( replaceString );
   	  	 
   	  	 buttonHolder = new JPanel( new GridLayout( 4, 1, 5, 5 ) );
   	  	 
   	  	 find = new JButton( "Find Next" );
   	  	 find.addActionListener( this );
   	  	 
   	  	 replace = new JButton( "Replace" );
   	  	 replace.addActionListener( this );
   	  	 
   	  	 replaceAll = new JButton( "Replace All" );
   	  	 replaceAll.addActionListener( this );
   	  	 
         cancel = new JButton( "Cancel" );
         cancel.addActionListener( this );
         
         buttonHolder.add( find );
         buttonHolder.add( replace );
         buttonHolder.add( replaceAll );
         buttonHolder.add( cancel );

   	  	 constraints.gridx = 2;
   	  	 constraints.gridy = 0;
   	  	 constraints.gridheight = 4;
   	  	 constraints.insets = new Insets( 0, 10, 0, 0 );
   	  	 
   	  	 gridBag.setConstraints( buttonHolder, constraints );
   	  	 
   	  	 container.add( buttonHolder );
   	  	 
         matchCase = new JCheckBox( "Match Case" );
         
         constraints.gridx = 0;
         constraints.gridy = 2;
   	  	 constraints.gridwidth = 2;
   	  	 constraints.gridheight = 1;
   	  	 constraints.insets = new Insets( 5, 0, 0, 0 );
            	  	 
   	  	 gridBag.setConstraints( matchCase, constraints );
   	  	 
   	  	 container.add( matchCase );
   	  	 
   	  	 numReplacedLabel = new JLabel( "Number of Replacements: " + totalReplaced, JLabel.CENTER );
   	  	 numReplacedLabel.setBorder( BorderFactory.createLoweredBevelBorder() );
   	  	 
         constraints.gridx = 0;
         constraints.gridy = 3;
   	  	 constraints.gridwidth = 2;
   	  	 constraints.gridheight = 1;
   	  	 constraints.ipadx = 30;
   	  	 constraints.insets = new Insets( 0, 0, 0, 0 );
            	  	 
   	  	 gridBag.setConstraints( numReplacedLabel, constraints );
   	  	 
   	  	 container.add( numReplacedLabel );
   	  	    	  	 
         setSize( width, height );
         
         Toolkit toolkit = Toolkit.getDefaultToolkit(); 
         Dimension dimension = toolkit.getScreenSize(); 
      
         setLocation ( dimension.width/2 - width/2, dimension.height/2 - height/2 ); 
      
         setTitle( "Search and Replace" );
         
         setVisible( true );   	  
   	  }
   	  
   	  public void actionPerformed( ActionEvent event )
      /****************************************************************
      * Method:
      *   actionPerformed takes care of the actions performed on this
      *   ReplaceDialog.
      * Inputs:
      *   ActionEvent event.
      * Outputs:
      *   none.
      ****************************************************************/
   	  {
   	  	 Object source = event.getSource();
   	  	 boolean matchFound = false;
   	  	 String textToFind = findString.getText();
   	  	 String replacementText = replaceString.getText();
   	  	 String searchString = document.getText();
   	  	 int location;
   	  	 int response;
   	  	 int i;
   	  	 
   	  	 if ( replacementText == null )
   	  	 {
   	  	    replacementText = "";	
   	  	 }
   	  	 
         if ( matchCase.isSelected() == false )
         {
            searchString = searchString.toUpperCase();	
            textToFind = textToFind.toUpperCase();	
         }
         
         if ( replacingAll == false && searchString != null )
         {
         	newlinesFound = 0;
         	
            for ( i = 0; i <= lastTextPosition; i++ )
            {
               if ( new StringBuffer( searchString ).charAt( i ) == '\n' )
               {
          	      ++newlinesFound;
               }
            }
         }
            
   	  	 if ( source == find )
   	  	 {
            location = searchString.indexOf( textToFind, lastTextPosition );
            
            if ( location != -1 )
            {
               document.setSelectionStart( location );
               document.setSelectionEnd( location + textToFind.length() );
               matchFound = true;
               
               if ( document.getSelectedText().equalsIgnoreCase( textToFind ) == false )
               {
                  for ( i = lastTextPosition; i <= location; i++ )
                  {
                     if ( new StringBuffer( searchString ).charAt( i ) == '\n' )
                     {
          	            ++newlinesFound;
                     }
                  }
      
                  document.setSelectionStart( location - newlinesFound );
                  document.setSelectionEnd( location + textToFind.length() - newlinesFound );
               }
                  
               lastTextPosition = location + 1;

               if ( replacingAll )
               {
                  this.actionPerformed( 
                     new ActionEvent( replace, ActionEvent.ACTION_PERFORMED, null ) );
               }                  	
            }
            
            if ( matchFound == false && replacingAll == false )
            {
           	   response = JOptionPane.showConfirmDialog( this,
         	                 "Continue search from beginning?", 
         	                 "End of file found",
                             JOptionPane.YES_NO_OPTION );
                        
               if ( response == JOptionPane.YES_OPTION )
               {                    
                  document.setCaretPosition( 0 );
              	  lastTextPosition = 0;
                  newlinesFound = 0;
                  this.actionPerformed( 
                     new ActionEvent( find, ActionEvent.ACTION_PERFORMED, null ) );
               }
               else
               {
               	  dispose();
               }
            }
   	  	 }
   	  	 
         if ( source == replace )
         {
            document.replaceSelection( replacementText );
            ++totalReplaced;
            numReplacedLabel.setText( "Number of Replacements: " + totalReplaced );
            this.actionPerformed( 
               new ActionEvent( find, ActionEvent.ACTION_PERFORMED, null ) );
         }
         
         if ( source == replaceAll )
         {
         	replacingAll = true;
            document.setCaretPosition( 0 );
       	    newlinesFound = 0;
       	    lastTextPosition = 0;
            this.actionPerformed( 
               new ActionEvent( find, ActionEvent.ACTION_PERFORMED, null ) );
         }

   	  	 if ( source == cancel )
   	  	 {
   	  	    dispose();	
   	  	 }   	  	 
   	  }
   }   

   private class DocumentFrame extends JInternalFrame 
   /*******************************************************************
   * Class:
   *   DocumentFrame is the internal frame that can be opened within
   *   the overall JDesktopPane.  It is initialized with a DnDTextPane,
   *   the file used to open the document, and a boolean value
   *   indicating whether it has been modified or not.
   *******************************************************************/   
   {
   	  private DnDTextPane document;
   	  private File file;
   	  private boolean modified;
   	  private Keymap keymap;
   	  
   	  public DocumentFrame( File file, DnDTextPane documentIn )
      /****************************************************************
      * Method:
      *   DocumentFrame constructor.
      * Inputs:
      *   File file, and DnDTextPane documentIn
      * Outputs:
      *   none.
      ****************************************************************/
   	  {
   	  	 super( "Untitled" + newDocumentNumber, true, true, true, true );
   	  	 modified = false;
   	  	 
         this.file = file;
 	 	 
 	 	 if ( file != null )
 	 	 {
 	 	    setTitle( file.getName() );	
 	 	 }

 	 	 if ( document == null )
 	 	 {
 	 	    document = new DnDTextPane();	
 	 	 }
 	 	 else
 	 	 {
 	 	    this.document = document;
 	 	 }
 	 	 
 	 	 keymap = document.addKeymap( "Keymap", document.getKeymap() );
 	 	 
 	 	 keymap.addActionForKeyStroke( (KeyStroke)cut.getValue( Action.ACCELERATOR_KEY ), cut );
 	 	 keymap.addActionForKeyStroke( (KeyStroke)copy.getValue( Action.ACCELERATOR_KEY ), copy );
 	 	 keymap.addActionForKeyStroke( (KeyStroke)paste.getValue( Action.ACCELERATOR_KEY ), paste );
 	 	 keymap.addActionForKeyStroke( (KeyStroke)selectAll.getValue( Action.ACCELERATOR_KEY ), selectAll );
 	 	 
 	 	 document.setKeymap( keymap );
 	 	 
         document.addMouseListener( popupListener );
         
         document.addCaretListener( new CaretMonitor() );
         
         document.getDocument().addDocumentListener( new DocumentMonitor() );
         
 	 	 getContentPane().add( new JScrollPane( document ) );
 	 	 
 	 	 document.requestFocus();
 	 	 document.setCaretPosition( 0 );
         
         setSize( DocumentEditor.this.getWidth() - 8, 
                  DocumentEditor.this.getHeight() - 75 );
                  
         FrameClosingListener frameClosingListener = new FrameClosingListener();
         
         addInternalFrameListener( frameClosingListener );

   	  	 setVisible( true );
   	  }
   	  
   	  public File getFile()
      /****************************************************************
      * Method:
      *   getFile returns the file associated with this DocumentFrame
      * Inputs:
      *   none.
      * Outputs:
      *   File file.
      ****************************************************************/
   	  {
   	  	 return file;
   	  }
   	  
   	  public void setFile( File file )
      /****************************************************************
      * Method:
      *   setFile sets the file for DocumentFrames that were not opened
      *   with an existing document.
      * Inputs:
      *   File file.
      * Outputs:
      *   none.
      ****************************************************************/
   	  {
   	  	 this.file = file;
   	  }
   	  
   	  public JTextPane getDocument()
      /****************************************************************
      * Method:
      *   getDocument returns the document associates with this
      *   DocumentFrame.
      * Inputs:
      *   none.
      * Outputs:
      *   JTextPane.
      ****************************************************************/
   	  {
   	  	 return document;
   	  }
   	  
   	  public boolean isModified()
      /****************************************************************
      * Method:
      *   isModified returns a boolean representing the state of the
      *   document in this DocumentFrame.
      * Inputs:
      *   none.
      * Outputs:
      *   boolean modified.
      ****************************************************************/
   	  {
   	  	 return modified;
   	  }
   	  
   	  public void setModified( boolean state )
      /****************************************************************
      * Method:
      *   setModified sets the state of this DocumentFrame.
      * Inputs:
      *   boolean state.
      * Outputs:
      *   none.
      ****************************************************************/
   	  {
   	  	 modified = state;
   	  }
   }
   
   private class FrameClosingListener extends InternalFrameAdapter
   /*******************************************************************
   * Class:
   *   FrameClosingListener responds to the event when a DocumentFrame
   *   is closed.  It makes sure that the file has been saved after
   *   any changes have been made.
   *******************************************************************/   
   {
   	  public void internalFrameClosed(InternalFrameEvent e) 
      /****************************************************************
      * Method:
      *   internalFrameClosed brings up a save dialog if the closing
      *   DocumentFrame has been modified.
      * Inputs:
      *   InternalFrameEvent e.
      * Outputs:
      *   none.
      ****************************************************************/
      {
         int response;
         String fileName;

         if ( ( (DocumentFrame)e.getSource() ).isModified() )
         {
         	fileName = ( (DocumentFrame)e.getSource() ).getTitle();
         	fileName = fileName.substring( 0, fileName.length() - 1 );
         
         	response = JOptionPane.showConfirmDialog( DocumentEditor.this,
         	              "Save Changes to \"" 
         	              + fileName + "\"?",
         	              "Save Changes?",
                          JOptionPane.YES_NO_OPTION );
                          
            if ( response == JOptionPane.YES_OPTION )
            {
               if ( ( (DocumentFrame)e.getSource() ).getFile() != null )
               {
                  try
                  {
                     fileOutputStream = new FileOutputStream( ( (DocumentFrame)e.getSource() ).getFile() );
                     editorKit.write( fileOutputStream, 
                                      ( (DocumentFrame)e.getSource() ).getDocument().getStyledDocument(), 0, 
                                      ( (DocumentFrame)e.getSource() ).getDocument().getStyledDocument().getLength() );
                  }
                  catch( Exception exception )
                  {
                     System.out.println( exception.getMessage() );
                  }
               }
               else
               {
                  int returnValue = fileChooser.showDialog( DocumentEditor.this, "Save As..." );
 
                  if ( returnValue == JFileChooser.APPROVE_OPTION ) 
                  {
                     File file = fileChooser.getSelectedFile();
                     file = new File( fileChooser.getCurrentDirectory(), file.getName() );

                     try
                     {
                        fileOutputStream = new FileOutputStream( file );
                        editorKit.write( fileOutputStream, 
                                         ( (DocumentFrame)e.getSource() ).getDocument().getStyledDocument(), 0, 
                                         ( (DocumentFrame)e.getSource() ).getDocument().getStyledDocument().getLength() );
                     }
                     catch( Exception otherException )
                     {
                        System.out.println( otherException.getMessage() );
                     }
                  }
               }
            }
         }
         
         --documentsOpen;
         
         openWindows.remove( (DocumentFrame)e.getSource() );
         
         updateWindowTitleMenu();
      }
   }
   
   private class CaretMonitor implements CaretListener
   /*******************************************************************
   * Class:
   *   CaretMonitor responds when the caret position is changed.
   *******************************************************************/   
   {
      public void caretUpdate( CaretEvent event ) 
      /****************************************************************
      * Method:
      *   caretUpdate sets the current DocumentFrame to a modified 
      *   state.
      * Inputs:
      *   CaretEvent event.
      * Outputs:
      *   none.
      ****************************************************************/
      {
         currentDocumentFrame = (DocumentFrame)documentPile.getSelectedFrame();
         
         if ( currentDocumentFrame.isModified() == false )
         {
            currentDocumentFrame.setTitle( currentDocumentFrame.getTitle() + "*" );
         }
         
         currentDocumentFrame.setModified( true );         
      }
   }
   
   private class DocumentMonitor implements DocumentListener 
   /*******************************************************************
   * Class:
   *   DocumentMonitor responds to changes made to the current
   *   DocumentFrame.
   *******************************************************************/   
   {
      public void insertUpdate(DocumentEvent e) 
      {
         System.out.println( "insert" );

         currentDocumentFrame = (DocumentFrame)documentPile.getSelectedFrame();
         
         if ( currentDocumentFrame.isModified() == false )
         {
            currentDocumentFrame.setTitle( currentDocumentFrame.getTitle() + "*" );
         }
         
         currentDocumentFrame.setModified( true );         
      }
     
      public void removeUpdate(DocumentEvent e) 
      {
         System.out.println( "remove" );

         currentDocumentFrame = (DocumentFrame)documentPile.getSelectedFrame();
         
         if ( currentDocumentFrame.isModified() == false )
         {
            currentDocumentFrame.setTitle( currentDocumentFrame.getTitle() + "*" );
         }
         
         currentDocumentFrame.setModified( true );         
      }
      
      public void changedUpdate(DocumentEvent e) 
      {
         System.out.println( "change" );

         currentDocumentFrame = (DocumentFrame)documentPile.getSelectedFrame();
         
         if ( currentDocumentFrame.isModified() == false )
         {
            currentDocumentFrame.setTitle( currentDocumentFrame.getTitle() + "*" );
         }
         
         currentDocumentFrame.setModified( true );         
      }
   }
   
   private class DnDTextPane extends JTextPane implements Printable,
                                                          DropTargetListener,
                                                          DragSourceListener,
                                                          DragGestureListener
   /*******************************************************************
   * Class:
   *   DnDTextPane is the editable portion of a DocumentFrame that has
   *   support for dragging and dropping text, as well as printing
   *   support.
   *******************************************************************/   
   {
      private boolean copyKeyPressed;
      private DragSource dragSource;
      private DropTarget dropTarget;
      private Point point;
      private boolean withinSelection;

      public DnDTextPane()
      /****************************************************************
      * Method:
      *   DnDTextPane constructor.
      * Inputs:
      *   none.
      * Outputs:
      *   none.
      ****************************************************************/
      {
         super();	

         copyKeyPressed = false;

         dragSource = new DragSource();
         dragSource.createDefaultDragGestureRecognizer( this, 
                       DnDConstants.ACTION_COPY_OR_MOVE, this );
         
         dropTarget = new DropTarget( this, this );
         
         setCaret( new DraggableCaret() );
         
         setSelectionColor( new Color( 70, 70, 200, 255 ) );
         
         addKeyListener( new KeyAdapter()
         {
         	public void keyPressed( KeyEvent event )
         	{
         	   int keyCode = event.getKeyCode();
         	   
         	   if ( keyCode == KeyEvent.VK_CONTROL )
         	   {
         	      copyKeyPressed = true;	
         	   }	
         	}

         	public void keyReleased( KeyEvent event )
         	{
         	   copyKeyPressed = false;
         	}
         });
         
         addMouseMotionListener( new MouseMotionAdapter()
         {      
            public void mouseMoved( MouseEvent event )
            {
               point = event.getPoint();
            }
         });
         
         setDoubleBuffered( true );
      }	

      public Point getPoint()
      /****************************************************************
      * Method:
      *   getPoint returns the point where the cursor currently
      *   resides.
      * Inputs:
      *   none.
      * Outputs:
      *   Point point.
      ****************************************************************/
      {
      	 return point;
      }

      public void dragOver( DropTargetDragEvent event )
      /****************************************************************
      * Method:
      *   dragOver sets the current location of the point of the cursor.
      * Inputs:
      *   DropTargetDragEvent event.
      * Outputs:
      *   none.
      ****************************************************************/
      {
         point = event.getLocation();
         
         paint( getGraphics() );
         
         getGraphics().draw3DRect( point.x, point.y + 30, 60, 20, true );
         
         if ( copyKeyPressed )
         {
            getGraphics().drawString( "Copy to...", point.x + 5, point.y + 45 );
         }
         else
         {
            getGraphics().drawString( "Move to...", point.x + 5, point.y + 45 );
         }
      }

      public void dragGestureRecognized( DragGestureEvent event ) 
      /****************************************************************
      * Method:
      *   dragGestureRecognized begins the dragging of the selected
      *   text.  If the control key is depressed, the text is copied,
      *   if not, it is cut.
      * Inputs:
      *   DragGestureEvent event.
      * Outputs:
      *   none.
      ****************************************************************/
      {
         if ( getSelectedText() != null 
              && ( (DraggableCaret)getCaret() ).isWithinSelection() )
         {
            StringSelection text = new StringSelection( getSelectedText() ); 
        
            if ( copyKeyPressed )
            {
               copy();
               dragSource.startDrag( event, DragSource.DefaultCopyDrop, text, this );
            }
            else
            {
               cut();	
               dragSource.startDrag( event, DragSource.DefaultMoveDrop, text, this );
            }            
         } 
      }

      public void drop( DropTargetDropEvent event ) 
      /****************************************************************
      * Method:
      *   drop determines the location of the caret and pastes the 
      *   selected text at that point.
      * Inputs:
      *   DropTargetDropEvent event.
      * Outputs:
      *   none.
      ****************************************************************/
      {
         try 
         {
            Transferable transferable = event.getTransferable();
                   
            if ( transferable.isDataFlavorSupported( DataFlavor.stringFlavor ) )
            {
               event.acceptDrop( DnDConstants.ACTION_COPY_OR_MOVE );
               String string = (String)transferable.getTransferData( DataFlavor.stringFlavor );
               event.getDropTargetContext().dropComplete( true );
               setCaretPosition( viewToModel( point ) );
               paste();
            } 
            else
            {
               event.rejectDrop();
            }
         }
         catch ( IOException exception ) 
         {
            exception.printStackTrace();
            System.err.println( "Exception" + exception.getMessage());
            event.rejectDrop();
         }  
         catch ( UnsupportedFlavorException ufException ) 
         {
            ufException.printStackTrace();
            System.err.println( "Exception" + ufException.getMessage() );
            event.rejectDrop();
         }
      }

      public void dragEnter( DragSourceDragEvent event ) {}
      public void dragEnter( DropTargetDragEvent event ) {} 
      public void dragOver( DragSourceDragEvent event ) {} 
      public void dragExit( DragSourceEvent event ) {}
      public void dragExit( DropTargetEvent event ) {}
      public void dropActionChanged ( DropTargetDragEvent event ) {}
      public void dropActionChanged( DragSourceDragEvent event ) {}
      public void dragDropEnd( DragSourceDropEvent event ) {}    

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
      /****************************************************************
      * Method:
      *   startPrint sets up the pieces necessary for the print method
      *   to do its job.
      * Inputs:
      *   none.
      * Outputs:
      *   none.
      ****************************************************************/
      { 
      	 PrinterJob printJob = PrinterJob.getPrinterJob();
         Book book = new Book();
            
         if ( printJob.printDialog() ) 
         {
          	PageFormat documentPageFormat = new PageFormat ();
            documentPageFormat = printJob.pageDialog( documentPageFormat );
            book.append( this, documentPageFormat );    
         
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
   
   private class DraggableCaret extends DefaultCaret
   /*******************************************************************
   * Class:
   *   DraggableCaret is what make Drag and Drop support possible.
   *******************************************************************/   
   {
      private boolean withinSelection;
      private JTextPane document;
      
      public DraggableCaret()
      /****************************************************************
      * Method:
      *   DraggableCaret constructor.
      * Inputs:
      *   none.
      * Outputs:
      *   none.
      ****************************************************************/
      {
         super();
         setBlinkRate( 500 );	
      	 withinSelection = false;
      }	
      
      public void mousePressed( MouseEvent event )
      /****************************************************************
      * Method:
      *   mousePressed determines whether the pointer is currently
      *   within a selected portion of text.  If it is, the boolean
      *   withinSelection is set to true.  If not, withinSelection
      *   is set to false, and the parent mousePressed method is called
      *   which will move the caret to the new position.
      * Inputs:
      *   MouseEvent event.
      * Outputs:
      *   none.
      ****************************************************************/
      {
         document = ( (DocumentFrame)documentPile.getSelectedFrame() ).getDocument();

      	 if ( document.getSelectionStart() <= document
      	      .viewToModel( ( (DnDTextPane)document ).getPoint() ) 
      	      && document.viewToModel( ( (DnDTextPane)document ).getPoint() ) 
      	      < document.getSelectionEnd() )
      	 {
      	    withinSelection = true;  	
         }
         else
         {
         	withinSelection = false;
         	super.mousePressed( event );
         }
      }
      
      public void mouseDragged( MouseEvent event )
      /****************************************************************
      * Method:
      *   mouseDragged calls its parent mouseDragged method if the
      *   the pointer is not within a selected portion of text.  If it
      *   is, it does nothing, so the drag gesture can be recognized by
      *   the appropriate drag and drop methods.
      * Inputs:
      *   MouseEvent event.
      * Outputs:
      *   none.
      ****************************************************************/
      {
      	 if ( !withinSelection )
      	 {
         	withinSelection = false;
         	super.mouseDragged( event );
         }
      }

      public boolean isWithinSelection()
      /****************************************************************
      * Method:
      *   isWithinSelection returns whether or not the Caret is within
      *   the currently selected text.
      * Inputs:
      *   none.
      * Outputs:
      *   boolean withinSelection.
      ****************************************************************/
      {
      	 return withinSelection;
      }
   } 

   public static void main( String [] args )
   /****************************************************************
   * Method:
   *   main instantiates a new DocumentEditor.
   * Inputs:
   *   N/A.
   * Outputs:
   *   none.
   ****************************************************************/
   {
   	  new DocumentEditor( false );
   }
}