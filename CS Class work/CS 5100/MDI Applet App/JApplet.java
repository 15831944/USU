/*
 * JApplet.java
 *
 * Created on March 22, 2002, 3:39 PM
 */

/**
 *
 * @author  Default
 */

import javax.swing.*;
import DocumentWindow;
import javax.swing.text.*;
import javax.swing.text.StyledEditorKit.FontFamilyAction.*;
import java.awt.event.*;
import javax.swing.JOptionPane;
import javax.swing.JDialog;
import java.beans.*;// this is for the property change listeners in the dialog\

public class JApplet extends javax.swing.JApplet {

    /** Creates new form JApplet */
    public JApplet() 
    {
        //openDocumentCount = 0;
        //document = new DocumentWindow[10];
        initComponents();
        fontAttributes = new SimpleAttributeSet[6];
        for (int i = 0; i< 6; i++)
            fontAttributes[i] = new SimpleAttributeSet();
        StyleConstants.setFontFamily(fontAttributes[0], "SansSerif");
        StyleConstants.setFontSize(fontAttributes[0], 10);
        StyleConstants.setFontFamily(fontAttributes[1], "SansSerif");
        StyleConstants.setFontSize(fontAttributes[1], 14);
        StyleConstants.setFontFamily(fontAttributes[2], "SansSerif");
        StyleConstants.setFontSize(fontAttributes[2], 16);
        StyleConstants.setFontFamily(fontAttributes[3], "Serif");
        StyleConstants.setFontSize(fontAttributes[3], 10);
        StyleConstants.setFontFamily(fontAttributes[4], "Serif");
        StyleConstants.setFontSize(fontAttributes[4], 14);
        StyleConstants.setFontFamily(fontAttributes[5], "Serif");
        StyleConstants.setFontSize(fontAttributes[5], 16);
    }

    private void initComponents() 
    {
        menuListener = new java.awt.event.ActionListener() 
        {
           public void actionPerformed(java.awt.event.ActionEvent evt) {
               MenuItemActionPerformed(evt);
           }
        };
        
        menuWindowListener = new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                WindowMenuItemActionPerformed(evt);
            }
        };
        
        menuBar = new javax.swing.JMenuBar();
        
        fileMenu = new javax.swing.JMenu("File");
        newMenuItem = new javax.swing.JMenuItem("New");
        fileMenu.add(newMenuItem);
        openMenuItem = new javax.swing.JMenuItem("Open");
        fileMenu.add(openMenuItem);
        saveMenuItem = new javax.swing.JMenuItem("Save");
        fileMenu.add(saveMenuItem);
        saveAsMenuItem = new javax.swing.JMenuItem("Save As...");
        fileMenu.add(saveAsMenuItem);
        exitMenuItem = new javax.swing.JMenuItem("Exit");
        newMenuItem.addActionListener(menuListener);
        openMenuItem.addActionListener(menuListener);
        saveMenuItem.addActionListener(menuListener);
        saveAsMenuItem.addActionListener(menuListener);
        exitMenuItem.addActionListener(menuListener);
        fileMenu.add(exitMenuItem);
        menuBar.add(fileMenu);
        
        editMenu = new javax.swing.JMenu("Edit");
        cutMenuItem = new javax.swing.JMenuItem("Cut");
        editMenu.add(cutMenuItem);
        copyMenuItem = new javax.swing.JMenuItem("Copy");
        editMenu.add(copyMenuItem);
        pasteMenuItem = new javax.swing.JMenuItem("Paste");
        editMenu.add(pasteMenuItem);
        selectAllMenuItem = new javax.swing.JMenuItem("Select All");
        editMenu.add(selectAllMenuItem);
        editMenu.addSeparator();
        findMenuItem = new javax.swing.JMenuItem("Find");
        editMenu.add(findMenuItem);
        replaceMenuItem = new javax.swing.JMenuItem("Replace");
        editMenu.add(replaceMenuItem);
        cutMenuItem.addActionListener(menuListener);
        copyMenuItem.addActionListener(menuListener);
        pasteMenuItem.addActionListener(menuListener);
        selectAllMenuItem.addActionListener(menuListener);
        findMenuItem.addActionListener(menuListener);
        replaceMenuItem.addActionListener(menuListener);
        menuBar.add(editMenu);
        
        String[] fontStrings = { "Serif 10pt", "Serif 12pt", "Serif 14pt", "Sans Serif 10pt", "Sans Serif 12pt","Sans Serif 14pt" };

        // Create the combo box, select the pig
        JComboBox fontCombo = new JComboBox(fontStrings);
        fontCombo.setSelectedIndex(0);
        fontCombo.addActionListener(new ActionListener() 
        {
            public void actionPerformed(ActionEvent e) 
            {
                JComboBox cb = (JComboBox)e.getSource();
                int index = cb.getSelectedIndex();
                DocumentWindow activeFrame = (DocumentWindow)desktopPane.getSelectedFrame();
                if (activeFrame.textPane.getSelectedText() == null)
                {
                    System.out.println("selected text is null");
                    //activeFrame.textPane.setFont(fontAttributes[index]);
                    //((DefaultEditorKit)activeFrame.editorKit).selectAllAction();
                    activeFrame.textPane.selectAll();
                }
                else
                {
                    System.out.println("selected text is not null, index ="+index);
      
                }
                activeFrame.textPane.setCharacterAttributes(fontAttributes[index],true);
                //activeFrame.textPane.setFont();
            }
        });
        menuBar.add(fontCombo);
        windowMenu = new JMenu("Window");
        menuBar.add(windowMenu);
        
        desktopPane = new javax.swing.JDesktopPane();
        //desktopPane.setSize(400,300);
        //setContentPane(desktopPane);
        //desktopPane.getContentPane().setJMenuBar(menuBar);
        getContentPane().setLayout(new java.awt.BorderLayout());
        getContentPane().add(desktopPane, java.awt.BorderLayout.CENTER);
        setJMenuBar(menuBar);
        //pack();
    }
    
    protected void addDocumentToWindowMenu(String windowName, DocumentWindow document)
    {
        JMenuItem newMenuItem = new MyWindowMenuItem(windowName,document);
        document.setMenuItem(newMenuItem);
        windowMenu.add(newMenuItem);
        newMenuItem.addActionListener(menuWindowListener);
    }
    
    protected void removeDocumentFromWindowMenu(DocumentWindow document)
    {
        windowMenu.remove(document.getMenuItem());
    }
    
    protected void createDocumentWindow(String filename) 
    {
        DocumentWindow window;
        String windowName;
        if (filename == null)
        {
            windowName = "Untitled = "+(openDocumentCount+1);
            window = new DocumentWindow(this, windowName,null);
        }
        else
        {
            windowName = filename;
            window = new DocumentWindow(this, windowName, filename);
        }
        
        window.setVisible(true); //necessary as of kestrel
        desktopPane.add(window);
        //window.setContentPane(desktopPane.);
        addDocumentToWindowMenu(windowName, window);

        try 
        {
            window.setLocation(xOffset*openDocumentCount, yOffset*openDocumentCount);
            window.setSelected(true);
        } 
        catch (java.beans.PropertyVetoException e) 
        {

        }
        openDocumentCount++;
    }

    private class MyWindowMenuItem extends JMenuItem
    {
        public DocumentWindow docWindow;
        public MyWindowMenuItem(String name, DocumentWindow dw)
        {
            super(name);
            docWindow = dw;
        }
    }
    
    
    class FindReplaceDialog extends JDialog 
    {
        JOptionPane optionPane;
        DocumentWindow activeFrame;
        JTextField findField;
        JTextField replaceField;
        boolean replace;
        String btnString1;
        
        public FindReplaceDialog(boolean r, DocumentWindow aFrame) 
        {
            replace = r;
            //super(activeFrame, true);
            setModal(false);
            activeFrame = aFrame;
            if (replace)
                setTitle("Replace");
            else
                setTitle("Find");
            
            JLabel findLabel = new JLabel(" Find ");
            findLabel.setSize(50,30);
            findField = new JTextField("");    
            findField.setSize(300, 30);
            JLabel replaceLabel = new JLabel(" Replace ");
            replaceLabel.setSize(50,30);
            replaceField = new JTextField("");
            replaceField.setSize(300,30);
            
            Object[] array;
        
            if (replace)
            {
                array = new Object[4];
                array[0] = findLabel;
                array[1] = findField;
                array[2] = replaceLabel;
                array[3] = replaceField;
                btnString1 = new String("Replace");
                setSize(300,180);
            }
            else
            {
                array = new Object[2];
                array[0] = findLabel;
                array[1] = findField;
                btnString1 = new String("Find");
                setSize(300,130);
            }
           
            final String btnString2 = "Cancel";
            
            Object[] options = {btnString1, btnString2};

            optionPane = new JOptionPane(array, 
                                        JOptionPane.QUESTION_MESSAGE,
                                        JOptionPane.OK_CANCEL_OPTION ,
                                        null,
                                        options,
                                        options[0]);
            setContentPane(optionPane);
            setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
            addWindowListener(new WindowAdapter() {
               public void windowClosing(WindowEvent we) {
                    /*
                     * Instead of directly closing the window,
                     * we're going to change the JOptionPane's
                     * value property.
                     */
                    optionPane.setValue(new Integer(JOptionPane.CLOSED_OPTION));

                }
            });

            optionPane.addPropertyChangeListener(new PropertyChangeListener() {
                public void propertyChange(PropertyChangeEvent e) {
                    String prop = e.getPropertyName();

                    if (isVisible() 
                     && (e.getSource() == optionPane)
                     && (prop.equals(JOptionPane.VALUE_PROPERTY) ||
                         prop.equals(JOptionPane.INPUT_VALUE_PROPERTY))) {
                        Object value = optionPane.getValue();

                        if (value == JOptionPane.UNINITIALIZED_VALUE) {
                            //ignore reset
                            return;
                        }

                        // Reset the JOptionPane's value.
                        // If you don't do this, then if the user
                        // presses the same button next time, no
                        // property change event will be fired.
                        optionPane.setValue(
                                JOptionPane.UNINITIALIZED_VALUE);

                        if (value.equals(btnString1)) 
                        {
                            // pressed ok
                            //setVisible(false);
                            String findString = findField.getText();
                            //String text = activeFrame.textPane.getText();
                            Segment textBuffer = new Segment();
                            try 
                            {
                                int currentDocumentPosition = activeFrame.textPane.getCaretPosition();
                                System.out.println("calling getText, cdp = "+currentDocumentPosition+", length = "+(activeFrame.lsd.getLength() - currentDocumentPosition));
                                activeFrame.lsd.getText(currentDocumentPosition, activeFrame.lsd.getLength() - currentDocumentPosition, textBuffer);
                                String sText = textBuffer.toString();
                
                                int nextPosition = sText.indexOf(findString,0);
                                System.out.println("searching within:\""+sText+"\" for \""+findString+"\", found at "+nextPosition);
                                if (nextPosition == -1)
                                {

                                }
                                else
                                {
                                    currentDocumentPosition = currentDocumentPosition + nextPosition;
                                    //activeFrame.textPane.
                                    int start = currentDocumentPosition;
                                    int end = currentDocumentPosition + findString.length();
                                    
                                    currentDocumentPosition += findString.length();
                                    //activeFrame.textPane.setCaretPosition(currentDocumentPosition);  
                                    //activeFrame.textPane.requestFocus();
                                    //activeFrame.textPane.setSelectionStart(start);
                                    //activeFrame.textPane.setSelectionEnd(start+len);
                                    //System.out.println("selection color = "+activeFrame.textPane.getSelectedTextColor().toString());
                                    //setVisible(false);
                                    //activeFrame.textPane.setSelectedTextColor(java.awt.Color.blue);
                                    //activeFrame.textPane.setSelectionColor(java.awt.Color.red);
                                    activeFrame.textPane.select(start,end);
                                    if (replace)
                                    {
                                        activeFrame.textPane.replaceSelection(replaceField.getText());
                                    }
                                    
                                }
                            }
                            catch(BadLocationException bpe)
                            {
                                
                                
                            }
                            
                        } 
                        else 
                        { // user closed dialog or clicked cancel   
                            setVisible(false);
                        }
                    }
                }
            });
        }
    }

    class CloseFrameDialog extends JDialog 
    {
        JOptionPane optionPane;
        JList fileCloseList;
        DocumentWindow frames[];
        
        public CloseFrameDialog() 
        {
            setModal(true);
           
            frames[] = (DocumentWindow[])desktopPane.getAllFrames();
            String fileNames[] = new String[openDocumentCount];
            for (int i = 0; i < openDocumentCount; i++)
            {
                fileNames[i] = new String(frames[i].getTitle());
            }
            // Create the combo box, select the pig
            fileCloseList = new JList(fileNames);
            
            Object[] array = {fileCloseList};
        
            setSize(300,300);
            
            final String btnString1 = "Close Windows";
            final String btnString2 = "Cancel";
            
            Object[] options = {btnString1, btnString2};

            optionPane = new JOptionPane(array, 
                                        JOptionPane.QUESTION_MESSAGE,
                                        JOptionPane.OK_CANCEL_OPTION ,
                                        null,
                                        options,
                                        options[0]);
            setContentPane(optionPane);
            setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
            addWindowListener(new WindowAdapter() {
               public void windowClosing(WindowEvent we) {
                    /*
                     * Instead of directly closing the window,
                     * we're going to change the JOptionPane's
                     * value property.
                     */
                    optionPane.setValue(new Integer(JOptionPane.CLOSED_OPTION));

                }
            });

            optionPane.addPropertyChangeListener(new PropertyChangeListener() {
                public void propertyChange(PropertyChangeEvent e) {
                    String prop = e.getPropertyName();

                    if (isVisible() 
                     && (e.getSource() == optionPane)
                     && (prop.equals(JOptionPane.VALUE_PROPERTY) ||
                         prop.equals(JOptionPane.INPUT_VALUE_PROPERTY))) {
                        Object value = optionPane.getValue();

                        if (value == JOptionPane.UNINITIALIZED_VALUE) {
                            //ignore reset
                            return;
                        }

                        // Reset the JOptionPane's value.
                        // If you don't do this, then if the user
                        // presses the same button next time, no
                        // property change event will be fired.
                        optionPane.setValue(
                                JOptionPane.UNINITIALIZED_VALUE);

                        if (value.equals(btnString1)) 
                        {
                            // pressed ok
                            //setVisible(false);
                            int indexes[] = fileCloseList.getSelectedIndices();
                            
                        } 
                        else 
                        { // user closed dialog or clicked cancel   
                            setVisible(false);
                        }
                    }
                }
            });
        }
    }

    private void MenuItemActionPerformed(java.awt.event.ActionEvent evt) 
    {
        //System.exit(0);
        // close...?
        
        String caption = ((JMenuItem)evt.getSource()).getText();
        if (caption.compareTo("New") == 0)
        {
            createDocumentWindow(null);
            DocumentWindow activeFrame = (DocumentWindow)desktopPane.getSelectedFrame();
            activeFrame.textPane.requestFocus();
        }
        else if(caption.compareTo("Open") == 0)
        {
            System.out.println("open");
            final JFileChooser fc = new JFileChooser();
            int returnVal = fc.showOpenDialog(this);
        
            if(returnVal == JFileChooser.APPROVE_OPTION)
            {
                createDocumentWindow(fc.getSelectedFile().getPath());
            }
            DocumentWindow activeFrame = (DocumentWindow)desktopPane.getSelectedFrame();
            activeFrame.textPane.requestFocus();
            //if (openDocumentCount < 10)
            //{
             
            //    openDocumentCount++;
            //}
        }
        else if(caption.compareTo("Save") == 0)
        {
            System.out.println("save");
            DocumentWindow activeFrame = (DocumentWindow)desktopPane.getSelectedFrame();
            if (activeFrame != null)
            {
                activeFrame.documentSave();
                activeFrame.textPane.requestFocus();
            }
        }
        else if(caption.compareTo("Save As...") == 0)
        {
            System.out.println("save as");
            DocumentWindow activeFrame = (DocumentWindow)desktopPane.getSelectedFrame();
            if (activeFrame != null)
            {
                activeFrame.documentSaveAs();
                activeFrame.textPane.requestFocus();
            }
        }
        else if(caption.compareTo("Exit") == 0)
        {
            System.exit(0);
        }
        else if(caption.compareTo("Cut") == 0)
        {
            DocumentWindow activeFrame = (DocumentWindow)desktopPane.getSelectedFrame();
            activeFrame.textPane.cut();
            activeFrame.textPane.requestFocus();
        }
        else if(caption.compareTo("Copy") == 0)
        {
            DocumentWindow activeFrame = (DocumentWindow)desktopPane.getSelectedFrame();
            activeFrame.textPane.copy();
            activeFrame.textPane.requestFocus();
        }
        else if(caption.compareTo("Paste") == 0)
        {
            DocumentWindow activeFrame = (DocumentWindow)desktopPane.getSelectedFrame();
            activeFrame.textPane.paste();
            activeFrame.textPane.requestFocus();
        }
        else if(caption.compareTo("Select All") == 0)
        {
            DocumentWindow activeFrame = (DocumentWindow)desktopPane.getSelectedFrame();
            activeFrame.textPane.selectAll();
            activeFrame.textPane.requestFocus();
        }
        else if(caption.compareTo("Find") == 0)
        {
            DocumentWindow activeFrame = (DocumentWindow)desktopPane.getSelectedFrame();
            //JOptionPane findDialog = new JOptionPane();
            //findDialog.s
            FindReplaceDialog fDlg = new FindReplaceDialog(false,activeFrame);
            fDlg.setVisible(true);
            //activeFrame.textPane.selectAll();
            //activeFrame.textPane.requestFocus();
        }
        else if(caption.compareTo("Replace") == 0)
        {
            DocumentWindow activeFrame = (DocumentWindow)desktopPane.getSelectedFrame();
            FindReplaceDialog fDlg = new FindReplaceDialog(true,activeFrame);
            fDlg.setVisible(true);
            //activeFrame.textPane.requestFocus();
        }
        else
        {
            //desktopPane.
            System.out.println("something else selected");
            
        }
    }
    private void WindowMenuItemActionPerformed(java.awt.event.ActionEvent evt) 
    {
        MyWindowMenuItem menuItem = (MyWindowMenuItem)evt.getSource();
        try
        {
            System.out.println(menuItem.docWindow.getTitle());
            menuItem.docWindow.setSelected(true);
        }
        catch(java.beans.PropertyVetoException e)
        {
            e.printStackTrace();
            System.out.println(e.getMessage());
        }
    }
    
    public int openDocumentCount = 0;
    //private DocumentWindow document[];

    // Variables declaration - do not modify
    private SimpleAttributeSet[] fontAttributes;
    private java.awt.event.ActionListener menuWindowListener;
    private java.awt.event.ActionListener menuListener;
    private javax.swing.JMenu windowMenu;
    private final int xOffset = 30;
    private final int yOffset = 30;
    private javax.swing.JMenuBar menuBar;
    private javax.swing.JMenu fileMenu;
    private javax.swing.JMenuItem newMenuItem;
    private javax.swing.JMenuItem openMenuItem;
    private javax.swing.JMenuItem saveMenuItem;
    private javax.swing.JMenuItem saveAsMenuItem;
    private javax.swing.JMenuItem exitMenuItem;
    private javax.swing.JMenu editMenu;
    private javax.swing.JMenuItem cutMenuItem;
    private javax.swing.JMenuItem copyMenuItem;
    private javax.swing.JMenuItem pasteMenuItem;
    private javax.swing.JMenuItem deleteMenuItem;
    private javax.swing.JMenuItem selectAllMenuItem;
    private javax.swing.JMenuItem findMenuItem;
    private javax.swing.JMenuItem replaceMenuItem;
    private javax.swing.JMenu helpMenu;
    private javax.swing.JMenuItem contentMenuItem;
    private javax.swing.JMenuItem aboutMenuItem;
    private javax.swing.JDesktopPane desktopPane;
    // End of variables declaration

}
