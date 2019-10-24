import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.text.*;
import com.symantec.itools.javax.swing.JToolBarSeparator;
import com.symantec.itools.javax.swing.icons.ImageIcon;

/**
 * A basic JFC 1.1 based application.
 */
public class JFrame1 extends javax.swing.JFrame
{
	public JFrame1()
	{
		// This code is automatically generated by Visual Cafe when you add
		// components to the visual environment. It instantiates and initializes
		// the components. To modify the code, only use code syntax that matches
		// what Visual Cafe can generate, or Visual Cafe may be unable to back
		// parse your Java file into its visual environment.
		//{{INIT_CONTROLS
		setJMenuBar(JMenuBar1);
		setTitle("JFC Application");
		setDefaultCloseOperation(javax.swing.JFrame.DO_NOTHING_ON_CLOSE);
		getContentPane().setLayout(new BorderLayout(0,0));
		setSize(488,309);
		setVisible(false);
		try {
			newIcon.setImageLocation(symantec.itools.net.RelativeURL.getURL("images/new.gif"));
		}
		catch (java.net.MalformedURLException error) { }
		//$$ newIcon.move(144,312);
		try {
			openIcon.setImageLocation(symantec.itools.net.RelativeURL.getURL("images/open.gif"));
		}
		catch (java.net.MalformedURLException error) { }
		//$$ openIcon.move(120,312);
		try {
			saveIcon.setImageLocation(symantec.itools.net.RelativeURL.getURL("images/save.gif"));
		}
		catch (java.net.MalformedURLException error) { }
		//$$ saveIcon.move(96,312);
		try {
			cutIcon.setImageLocation(symantec.itools.net.RelativeURL.getURL("images/cut.gif"));
		}
		catch (java.net.MalformedURLException error) { }
		//$$ cutIcon.move(72,312);
		try {
			copyIcon.setImageLocation(symantec.itools.net.RelativeURL.getURL("images/copy.gif"));
		}
		catch (java.net.MalformedURLException error) { }
		//$$ copyIcon.move(48,312);
		try {
			pasteIcon.setImageLocation(symantec.itools.net.RelativeURL.getURL("images/paste.gif"));
		}
		catch (java.net.MalformedURLException error) { }
		//$$ pasteIcon.move(24,312);
		try {
			aboutIcon.setImageLocation(symantec.itools.net.RelativeURL.getURL("images/about.gif"));
		}
		catch (java.net.MalformedURLException error) { }
		//$$ aboutIcon.move(0,312);
		saveFileDialog.setMode(FileDialog.SAVE);
		saveFileDialog.setTitle("Save");
		//$$ saveFileDialog.move(24,336);
		openFileDialog.setMode(FileDialog.LOAD);
		openFileDialog.setTitle("Open");
		//$$ openFileDialog.move(0,336);
		JPanel2.setLayout(new FlowLayout(FlowLayout.LEFT,0,0));
		getContentPane().add(BorderLayout.NORTH, JPanel2);
		JPanel2.setBounds(0,0,488,33);
		JToolBar1.setAlignmentY(0.222222F);
		JPanel2.add(JToolBar1);
		JToolBar1.setBounds(0,0,395,33);
		newButton.setDefaultCapable(false);
		newButton.setToolTipText("Create a new document");
		newButton.setMnemonic((int)'N');
		JToolBar1.add(newButton);
		newButton.setBounds(16,4,51,27);
		openButton.setDefaultCapable(false);
		openButton.setToolTipText("Open an existing document");
		openButton.setMnemonic((int)'O');
		JToolBar1.add(openButton);
		openButton.setBounds(67,4,51,27);
		saveButton.setDefaultCapable(false);
		saveButton.setToolTipText("Save the active document");
		saveButton.setMnemonic((int)'S');
		JToolBar1.add(saveButton);
		saveButton.setBounds(118,4,51,27);
		JToolBar1.add(JToolBarSeparator1);
		JToolBarSeparator1.setBounds(169,2,10,5);
		cutButton.setDefaultCapable(false);
		cutButton.setToolTipText("Cut the selection and put it on the Clipboard");
		cutButton.setMnemonic((int)'T');
		JToolBar1.add(cutButton);
		cutButton.setBounds(179,4,51,27);
		copyButton.setDefaultCapable(false);
		copyButton.setToolTipText("Copy the selection and put it on the Clipboard");
		copyButton.setMnemonic((int)'C');
		JToolBar1.add(copyButton);
		copyButton.setBounds(230,4,51,27);
		pasteButton.setDefaultCapable(false);
		pasteButton.setToolTipText("Insert Clipboard contents");
		pasteButton.setMnemonic((int)'P');
		JToolBar1.add(pasteButton);
		pasteButton.setBounds(281,4,51,27);
		JToolBar1.add(JToolBarSeparator2);
		JToolBarSeparator2.setBounds(332,2,10,5);
		aboutButton.setDefaultCapable(false);
		aboutButton.setToolTipText("Display program information, version number and copyright");
		aboutButton.setMnemonic((int)'A');
		JToolBar1.add(aboutButton);
		aboutButton.setBounds(342,4,51,27);
		JPanel1.setLayout(null);
		getContentPane().add(BorderLayout.CENTER, JPanel1);
		JPanel1.setBounds(0,33,488,276);
		JPanel1.add(JTextPane1);
		JTextPane1.setBounds(2,0,484,274);
		//$$ JMenuBar1.move(168,312);
		fileMenu.setText("File");
		fileMenu.setActionCommand("File");
		fileMenu.setMnemonic((int)'F');
		JMenuBar1.add(fileMenu);
		newItem.setText("New");
		newItem.setActionCommand("New");
		newItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_N, java.awt.Event.CTRL_MASK));
		newItem.setMnemonic((int)'N');
		fileMenu.add(newItem);
		openItem.setText("Open...");
		openItem.setActionCommand("Open...");
		openItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_O, java.awt.Event.CTRL_MASK));
		openItem.setMnemonic((int)'O');
		fileMenu.add(openItem);
		saveItem.setText("Save");
		saveItem.setActionCommand("Save");
		saveItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_S, java.awt.Event.CTRL_MASK));
		saveItem.setMnemonic((int)'S');
		fileMenu.add(saveItem);
		saveAsItem.setText("Save As...");
		saveAsItem.setActionCommand("Save As...");
		saveAsItem.setMnemonic((int)'A');
		fileMenu.add(saveAsItem);
		fileMenu.add(JSeparator1);
		exitItem.setText("Exit");
		exitItem.setActionCommand("Exit");
		exitItem.setMnemonic((int)'X');
		fileMenu.add(exitItem);
		editMenu.setText("Edit");
		editMenu.setActionCommand("Edit");
		editMenu.setMnemonic((int)'E');
		JMenuBar1.add(editMenu);
		cutItem.setText("Cut");
		cutItem.setActionCommand("Cut");
		cutItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_X, java.awt.Event.CTRL_MASK));
		cutItem.setMnemonic((int)'T');
		editMenu.add(cutItem);
		copyItem.setText("Copy");
		copyItem.setActionCommand("Copy");
		copyItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_C, java.awt.Event.CTRL_MASK));
		copyItem.setMnemonic((int)'C');
		editMenu.add(copyItem);
		pasteItem.setText("Paste");
		pasteItem.setActionCommand("Paste");
		pasteItem.setAccelerator(javax.swing.KeyStroke.getKeyStroke(java.awt.event.KeyEvent.VK_V, java.awt.Event.CTRL_MASK));
		pasteItem.setMnemonic((int)'P');
		editMenu.add(pasteItem);
		helpMenu.setText("Help");
		helpMenu.setActionCommand("Help");
		helpMenu.setMnemonic((int)'H');
		JMenuBar1.add(helpMenu);
		aboutItem.setText("About...");
		aboutItem.setActionCommand("About...");
		aboutItem.setMnemonic((int)'A');
		helpMenu.add(aboutItem);
		openItem.setIcon(openIcon);
		saveButton.setIcon(saveIcon);
		newButton.setIcon(newIcon);
		aboutItem.setIcon(aboutIcon);
		newItem.setIcon(newIcon);
		openButton.setIcon(openIcon);
		aboutButton.setIcon(aboutIcon);
		pasteButton.setIcon(pasteIcon);
		cutButton.setIcon(cutIcon);
		pasteItem.setIcon(pasteIcon);
		copyItem.setIcon(copyIcon);
		cutItem.setIcon(cutIcon);
		copyButton.setIcon(copyIcon);
		saveItem.setIcon(saveIcon);
		//}}

		//{{INIT_MENUS
		//}}

		//{{REGISTER_LISTENERS
		SymWindow aSymWindow = new SymWindow();
		this.addWindowListener(aSymWindow);
		SymAction lSymAction = new SymAction();
		openItem.addActionListener(lSymAction);
		saveItem.addActionListener(lSymAction);
		exitItem.addActionListener(lSymAction);
		aboutItem.addActionListener(lSymAction);
		openButton.addActionListener(lSymAction);
		saveButton.addActionListener(lSymAction);
		aboutButton.addActionListener(lSymAction);
		SymKey aSymKey = new SymKey();
		JTextPane1.addKeyListener(aSymKey);
		//}}
		standard = (Style)JTextPane1.getLogicalStyle();
		comment = JTextPane1.addStyle("Comment", standard);
		StyleConstants.setForeground(comment, Color.green);
		indent = JTextPane1.addStyle("Indent", standard);
		StyleConstants.setLeftIndent(indent, 10);
		d = (DefaultStyledDocument)JTextPane1.getDocument();
	}

    /**
     * Creates a new instance of JFrame1 with the given title.
     * @param sTitle the title for the new frame.
     * @see #JFrame1()
     */
	public JFrame1(String sTitle)
	{
		this();
		setTitle(sTitle);
	}
	
	/**
	 * The entry point for this application.
	 * Sets the Look and Feel to the System Look and Feel.
	 * Creates a new JFrame1 and makes it visible.
	 */
	static public void main(String args[])
	{
		try {
		    // Add the following code if you want the Look and Feel
		    // to be set to the Look and Feel of the native system.
		    /*
		    try {
		        UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		    } 
		    catch (Exception e) { 
		    }
		    */

			//Create a new instance of our application's frame, and make it visible.
			(new JFrame1()).setVisible(true);
		} 
		catch (Throwable t) {
			t.printStackTrace();
			//Ensure the application exits with an error condition.
			System.exit(1);
		}
	}

    /**
     * Notifies this component that it has been added to a container
     * This method should be called by <code>Container.add</code>, and 
     * not by user code directly.
     * Overridden here to adjust the size of the frame if needed.
     * @see java.awt.Container#removeNotify
     */
	public void addNotify()
	{
		// Record the size of the window prior to calling parents addNotify.
		Dimension size = getSize();
		
		super.addNotify();
		
		if (frameSizeAdjusted)
			return;
		frameSizeAdjusted = true;
		
		// Adjust size of frame according to the insets and menu bar
		javax.swing.JMenuBar menuBar = getRootPane().getJMenuBar();
		int menuBarHeight = 0;
		if (menuBar != null)
		    menuBarHeight = menuBar.getPreferredSize().height;
		Insets insets = getInsets();
		setSize(insets.left + insets.right + size.width, insets.top + insets.bottom + size.height + menuBarHeight);
	}

	// Used by addNotify
	boolean frameSizeAdjusted = false;

	//{{DECLARE_CONTROLS
	com.symantec.itools.javax.swing.icons.ImageIcon newIcon = new com.symantec.itools.javax.swing.icons.ImageIcon();
	com.symantec.itools.javax.swing.icons.ImageIcon openIcon = new com.symantec.itools.javax.swing.icons.ImageIcon();
	com.symantec.itools.javax.swing.icons.ImageIcon saveIcon = new com.symantec.itools.javax.swing.icons.ImageIcon();
	com.symantec.itools.javax.swing.icons.ImageIcon cutIcon = new com.symantec.itools.javax.swing.icons.ImageIcon();
	com.symantec.itools.javax.swing.icons.ImageIcon copyIcon = new com.symantec.itools.javax.swing.icons.ImageIcon();
	com.symantec.itools.javax.swing.icons.ImageIcon pasteIcon = new com.symantec.itools.javax.swing.icons.ImageIcon();
	com.symantec.itools.javax.swing.icons.ImageIcon aboutIcon = new com.symantec.itools.javax.swing.icons.ImageIcon();
	java.awt.FileDialog saveFileDialog = new java.awt.FileDialog(this);
	java.awt.FileDialog openFileDialog = new java.awt.FileDialog(this);
	javax.swing.JPanel JPanel2 = new javax.swing.JPanel();
	javax.swing.JToolBar JToolBar1 = new javax.swing.JToolBar();
	javax.swing.JButton newButton = new javax.swing.JButton();
	javax.swing.JButton openButton = new javax.swing.JButton();
	javax.swing.JButton saveButton = new javax.swing.JButton();
	com.symantec.itools.javax.swing.JToolBarSeparator JToolBarSeparator1 = new com.symantec.itools.javax.swing.JToolBarSeparator();
	javax.swing.JButton cutButton = new javax.swing.JButton();
	javax.swing.JButton copyButton = new javax.swing.JButton();
	javax.swing.JButton pasteButton = new javax.swing.JButton();
	com.symantec.itools.javax.swing.JToolBarSeparator JToolBarSeparator2 = new com.symantec.itools.javax.swing.JToolBarSeparator();
	javax.swing.JButton aboutButton = new javax.swing.JButton();
	javax.swing.JPanel JPanel1 = new javax.swing.JPanel();
	javax.swing.JTextPane JTextPane1 = new javax.swing.JTextPane();
	javax.swing.JMenuBar JMenuBar1 = new javax.swing.JMenuBar();
	javax.swing.JMenu fileMenu = new javax.swing.JMenu();
	javax.swing.JMenuItem newItem = new javax.swing.JMenuItem();
	javax.swing.JMenuItem openItem = new javax.swing.JMenuItem();
	javax.swing.JMenuItem saveItem = new javax.swing.JMenuItem();
	javax.swing.JMenuItem saveAsItem = new javax.swing.JMenuItem();
	javax.swing.JSeparator JSeparator1 = new javax.swing.JSeparator();
	javax.swing.JMenuItem exitItem = new javax.swing.JMenuItem();
	javax.swing.JMenu editMenu = new javax.swing.JMenu();
	javax.swing.JMenuItem cutItem = new javax.swing.JMenuItem();
	javax.swing.JMenuItem copyItem = new javax.swing.JMenuItem();
	javax.swing.JMenuItem pasteItem = new javax.swing.JMenuItem();
	javax.swing.JMenu helpMenu = new javax.swing.JMenu();
	javax.swing.JMenuItem aboutItem = new javax.swing.JMenuItem();
	//}}

	//{{DECLARE_MENUS
	//}}
	Style standard;
	Style comment;
	Style indent;
	DefaultStyledDocument d;


	void exitApplication()
	{
		try {
	    	// Beep
	    	Toolkit.getDefaultToolkit().beep();
	    	// Show a confirmation dialog
	    	int reply = JOptionPane.showConfirmDialog(this, 
	    	                                          "Do you really want to exit?", 
	    	                                          "JFC Application - Exit" , 
	    	                                          JOptionPane.YES_NO_OPTION, 
	    	                                          JOptionPane.QUESTION_MESSAGE);
			// If the confirmation was affirmative, handle exiting.
			if (reply == JOptionPane.YES_OPTION)
			{
		    	this.setVisible(false);    // hide the Frame
		    	this.dispose();            // free the system resources
		    	System.exit(0);            // close the application
			}
		} catch (Exception e) {
		}
	}

	class SymWindow extends java.awt.event.WindowAdapter
	{
		public void windowClosing(java.awt.event.WindowEvent event)
		{
			Object object = event.getSource();
			if (object == JFrame1.this)
				JFrame1_windowClosing(event);
		}
	}

	void JFrame1_windowClosing(java.awt.event.WindowEvent event)
	{
		// to do: code goes here.
			 
		JFrame1_windowClosing_Interaction1(event);
	}

	void JFrame1_windowClosing_Interaction1(java.awt.event.WindowEvent event) {
		try {
			this.exitApplication();
		} catch (Exception e) {
		}
	}

	class SymAction implements java.awt.event.ActionListener
	{
		public void actionPerformed(java.awt.event.ActionEvent event)
		{
			Object object = event.getSource();
			if (object == openItem)
				openItem_actionPerformed(event);
			else if (object == saveItem)
				saveItem_actionPerformed(event);
			else if (object == exitItem)
				exitItem_actionPerformed(event);
			else if (object == aboutItem)
				aboutItem_actionPerformed(event);
			else if (object == openButton)
				openButton_actionPerformed(event);
			else if (object == saveButton)
				saveButton_actionPerformed(event);
			else if (object == aboutButton)
				aboutButton_actionPerformed(event);
		}
	}

	void openItem_actionPerformed(java.awt.event.ActionEvent event)
	{
		// to do: code goes here.
			 
		openItem_actionPerformed_Interaction1(event);
	}

	void openItem_actionPerformed_Interaction1(java.awt.event.ActionEvent event) {
		try {
			// openFileDialog Show the FileDialog
			openFileDialog.setVisible(true);
		} catch (Exception e) {
		}
	}

	void saveItem_actionPerformed(java.awt.event.ActionEvent event)
	{
		// to do: code goes here.
			 
		saveItem_actionPerformed_Interaction1(event);
	}

	void saveItem_actionPerformed_Interaction1(java.awt.event.ActionEvent event) {
		try {
			// saveFileDialog Show the FileDialog
			saveFileDialog.setVisible(true);
		} catch (Exception e) {
		}
	}

	void exitItem_actionPerformed(java.awt.event.ActionEvent event)
	{
		// to do: code goes here.
			 
		exitItem_actionPerformed_Interaction1(event);
	}

	void exitItem_actionPerformed_Interaction1(java.awt.event.ActionEvent event) {
		try {
			this.exitApplication();
		} catch (Exception e) {
		}
	}

	void aboutItem_actionPerformed(java.awt.event.ActionEvent event)
	{
		// to do: code goes here.
			 
		aboutItem_actionPerformed_Interaction1(event);
	}

	void aboutItem_actionPerformed_Interaction1(java.awt.event.ActionEvent event) {
		try {
			// JAboutDialog Create with owner and show as modal
			{
				JAboutDialog JAboutDialog1 = new JAboutDialog(this);
				JAboutDialog1.setModal(true);
				JAboutDialog1.show();
			}
		} catch (Exception e) {
		}
	}

	void openButton_actionPerformed(java.awt.event.ActionEvent event)
	{
		// to do: code goes here.
			 
		openButton_actionPerformed_Interaction1(event);
	}

	void openButton_actionPerformed_Interaction1(java.awt.event.ActionEvent event) {
		try {
			// openFileDialog Show the FileDialog
			openFileDialog.setVisible(true);
		} catch (Exception e) {
		}
	}

	void saveButton_actionPerformed(java.awt.event.ActionEvent event)
	{
		// to do: code goes here.
			 
		saveButton_actionPerformed_Interaction1(event);
	}

	void saveButton_actionPerformed_Interaction1(java.awt.event.ActionEvent event) {
		try {
			// saveFileDialog Show the FileDialog
			saveFileDialog.setVisible(true);
		} catch (Exception e) {
		}
	}

	void aboutButton_actionPerformed(java.awt.event.ActionEvent event)
	{
		// to do: code goes here.
			 
		aboutButton_actionPerformed_Interaction1(event);
	}

	void aboutButton_actionPerformed_Interaction1(java.awt.event.ActionEvent event) {
		try {
			// JAboutDialog Create with owner and show as modal
			{
				JAboutDialog JAboutDialog1 = new JAboutDialog(this);
				JAboutDialog1.setModal(true);
				JAboutDialog1.show();
			}
		} catch (Exception e) {
		}
	}

	class SymKey extends java.awt.event.KeyAdapter
	{
		public void keyPressed(java.awt.event.KeyEvent event)
		{
			Object object = event.getSource();
			if (object == JTextPane1)
				JTextPane1_keyPressed(event);
		}

		public void keyTyped(java.awt.event.KeyEvent event)
		{
			Object object = event.getSource();
			if (object == JTextPane1)
				JTextPane1_keyTyped(event);
		}
	}

	void JTextPane1_keyTyped(java.awt.event.KeyEvent event)
	{
		// to do: code goes here.
			 
		JTextPane1_keyTyped_Interaction1(event);
	}

	void JTextPane1_keyTyped_Interaction1(java.awt.event.KeyEvent event)
	{
		try {
		    char c = event.getKeyChar();
		    if (c != '/' && c != '*') return;
		    switch(c)
		    {
		        case '/':
		            JTextPane1.setCharacterAttributes(comment, true);
		            break;
		        case '*':    
		            JTextPane1.setCharacterAttributes(standard, true);	
		            break;
		    }
		} catch (java.lang.Exception e) {
		}
	}

	void JTextPane1_keyPressed(java.awt.event.KeyEvent event)
	{
		// to do: code goes here.
			 
		JTextPane1_keyPressed_Interaction1(event);
	}

	void JTextPane1_keyPressed_Interaction1(java.awt.event.KeyEvent event)
	{
		try {
		    switch (event.getKeyCode())
		    {
		        case KeyEvent.VK_TAB:
		            if (!event.isShiftDown())
		                JTextPane1.setParagraphAttributes(indent, true);
		            else JTextPane1.setParagraphAttributes(standard, true);	
		            break;
		        case KeyEvent.VK_F1:
		            if (!event.isShiftDown())
		            {    
		                d.setParagraphAttributes(6, 20, indent, true);
		            }
		            else d.setParagraphAttributes(6, 20, standard, true);	
		            break;
		        case KeyEvent.VK_F2:
		            if (!event.isShiftDown())
		            {    
		                d.setCharacterAttributes(3, 10, comment, true);
		            }
		            else d.setCharacterAttributes(3, 10, standard, true);	
		            break;
		    }
		    } catch (java.lang.Exception e) {
		}
	}
}