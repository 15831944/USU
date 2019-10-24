/*
 * Class.java
 *
 * Created on February 25, 2002, 5:39 PM
 */

/**
 *
 * @author  Mark Salisbury
 * @version 
 */
import java.awt.*;
import javax.swing.*;
//import java.awt.event.*;
//import javax.swing.event.*;
import javax.swing.border.BevelBorder;

public class Album extends JPanel
{
    private JPanel titlePanel;
    private JPanel picturePanel;
    private JLabel pictureLabel;
    private JPanel messagePanel;
    private JPanel buttonPanel;
    private JLabel titleLabel;
    private JLabel messageLabel;
    Image images[];
    private static JFrame frame;

    /*
    public void openAlbum()
    {
        //Create a file chooser
        final JFileChooser fc = new JFileChooser();
        
        ExampleFileFilter filter = new ExampleFileFilter(
                 new String("gif"), "JPEG & GIF Images");
        
        fc.addChoosableFileFilter(filter);
 
        //In response to a button click:
        int returnVal = fc.showOpenDialog(this);
        if (returnVal != 0)
        {
            fc.getSelectedFile();
        }   
    }
    */
    public Album()
    {
      create();
      //loadImages();
    }

    protected void create()
    {
        /*
      setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
      titlePanel = new JPanel();
      titleLabel = new JLabel("Photo Album Program - No Album Loaded");
      titlePanel.add(titleLabel);

      picturePanel = new JPanel();
      picturePanel.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
      pictureLabel = new JLabel();
      picturePanel.setSize(500,500);
      picturePanel.setLayout(new CardLayout());

      messagePanel = new JPanel();
      messageLabel = new JLabel("No Image Loaded - Choose Open from the File Menu");
      messagePanel.add(messageLabel);

      buttonPanel = new JPanel();
      JButton pPhoto = new JButton("Previous Photo");
      JButton nPhoto = new JButton("Next Photo");
      buttonPanel.add(pPhoto);
      buttonPanel.add(nPhoto);

      //setLayout(new BorderLayout());
      add(titlePanel);//, BorderLayout.NORTH);
      add(picturePanel);//, BorderLayout.CENTER);
      add(messagePanel);//l;, BorderLayout.SOUTH);
      add(buttonPanel);//, BorderLayout.SOUTH);
         */
    }
    
    protected void loadFile(String fileName)
    {
        pictureLabel.setIcon(new ImageIcon(fileName));
    }

    protected void loadAlbum()
    {

    }

    public Dimension getPreferredSize()
    {
        return new Dimension(600,600);
    }

    public Dimension getMinimumSize()
    {
        return getPreferredSize();
    }

    public static void main(String [] args)
    {
        frame = new JFrame("Album for CS 5100");
        Album app = new Album();
        frame.getContentPane().add(app);
        frame.pack();
        frame.setVisible(true);
    }
    /*
    private void createMenus()
    {
        JMenu fileMenu = new JMenu("File");
        MyMenuItem mi11 = new MyMenuItem("Open Album (Ctrl+O)",1);
        MenuItemListener miListener = new MenuItemListener();
        mi11.addActionListener(miListener);
        MyMenuItem mi12 = new MyMenuItem("Exit",2);
        mi12.addActionListener(miListener);
        fileMenu.add(mi11);
        fileMenu.addSeparator();
        fileMenu.add(mi12);

        JMenu optionsMenu = new JMenu("Help");
        MyMenuItem mi21 = new MyMenuItem("About...",3);
        mi21.addActionListener(miListener);
        MyMenuItem mi22 = new MyMenuItem("Album Files...",4);
        mi22.addActionListener(miListener);

        optionsMenu.add(mi21);
        optionsMenu.add(mi22);

        JMenuBar menuBar = new JMenuBar();
        menuBar.add(fileMenu);
        menuBar.add(optionsMenu);
        frame.setJMenuBar(menuBar);
    }
    
    class MenuItemListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            switch (((MyMenuItem)e.getSource()).id)
            {
            case 1:
            System.out.println("option 1");
            break;
            case 2:
            System.out.println("option 2");
            break;
            case 3:
            System.out.println("option 3");
            break;
            case 4:
            System.out.println("option 4");
            break;
            case 5:
            System.out.println("option 5");
            break;
            }
        }
    }
    
    class MyMenuItem extends JMenuItem
    {
        public int id;
        public MyMenuItem(String name, int Id)
        {
            super(name);
            id = Id;
        }
    }
     */
}


