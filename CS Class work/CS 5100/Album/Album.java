/*
 * Album.java
 *
 * Created on February 25, 2002, 10:10 PM
 */

package Album;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import javax.swing.event.*;
import javax.swing.border.BevelBorder;
import ExampleFileFilter;
import java.io.File;
import java.io.BufferedReader;
import java.io.FileReader;
/**
 *
 * @author  Mark Salisbury
 */
public class Album extends javax.swing.JPanel {

    /** Creates new form Album */
    public Album()
    {
      create();
      //loadImages();
    }

    private JPanel titlePanel;
    private JPanel picturePanel;
    private JLabel pictureLabel;
    private JPanel messagePanel;
    private JPanel buttonPanel;
    private JLabel titleLabel;
    private JLabel messageLabel;
    //Image images[];
    private static Album pAlbum;
    private static JFrame frame;
    private JButton pPhoto;
    private JButton nPhoto;
    private String fileNames[];
    private String fileComments[];
    private int nFiles;
    private int currentFileIndex = 0;
    private String albumTitle;
    private boolean startMode = false;
    
    /*
    public void openAlbum()
    {
        //Create a file chooser
        final JFileChooser fc = new JFileChooser();
        
        ExampleFileFilter filter = new ExampleFileFilter(new String("alb"), "Album Files");
        //filter.addExtenstion(new String("jpg"));
        fc.addChoosableFileFilter(filter);
        fc.setCurrentDirectory(new File ("."));
        //In response to a button click:
        int returnVal = fc.showOpenDialog(this);
        if (returnVal != 0)
        {
            albumTitle = fc.getSelectedFile().getName();
            
            try 
            {
                BufferedReader in = new BufferedReader(new FileReader(fc.getSelectedFile().getPath()));
                String thisLine;
                thisLine = in.readLine();
                if (thisLine != null)
                {
                    nFiles = Integer.parseInt(thisLine);
                }
                fileNames = new String[nFiles];
                fileComments = new String[nFiles];
                
                for (int i = 0; i < nFiles; i++)
                {
                    fileNames[i] = in.readLine();
                    fileComments[i] = in.readLine();
                }
                setDisplay(0);
            }
            catch (Exception e) 
            {
                e.printStackTrace();
            }
            
        }   
    }
    */
    /*
    private void startDisplay()
    {
        startMode = true;    
        titleLabel.setText(albumTitle);
        messageLabel.setText("");
        pPhoto.setVisible(false);
        nPhoto.setText("Start");
        nPhoto.setVisible(true);
    }
    
    private void setDisplay(int imageIndex)
    {
          
        
        
    }
    /*
    public class buttonListener implements ActionListener
    {
        public void actionPerformed(java.awt.event.ActionEvent actionEvent)
        {
            JButton button = (JButton)actionEvent.getSource();
            if (button.getText().compareTo(new String("Previous Photo"))==0)
            {
                System.out.println("Previous Photo");
            }
            else
            {
                if (startMode == true)
                {
                    startMode = false;
                    pPhoto.setVisible(true);
                    nPhoto.setText("Next Photo");
                    setDisplay(0);
                }
                System.out.println("Next Photo");
            }
        }
    }
    */  
    protected void create()
    {
        
      setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
      titlePanel = new JPanel();
      titleLabel = new JLabel("Photo Album Program - No Album Loaded");
      titlePanel.add(titleLabel);

      picturePanel = new JPanel();
      picturePanel.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
      pictureLabel = new JLabel();
      pictureLabel.setSize(500,500);
      pictureLabel.setMaximumSize(new Dimension(500,500));
      pictureLabel.setPreferredSize(new Dimension(500,500));
      pictureLabel.setMinimumSize(new Dimension(500,500));
      picturePanel.add(pictureLabel);
      
      messagePanel = new JPanel();
      messageLabel = new JLabel("No Image Loaded - Choose Open from the File Menu");
      messagePanel.add(messageLabel);

      buttonPanel = new JPanel();
      pPhoto = new JButton("Previous Photo");
      //pPhoto.addActionListener(new buttonListener());
      nPhoto = new JButton("Next Photo");
      //nPhoto.addActionListener(new buttonListener());
      buttonPanel.add(pPhoto);
      buttonPanel.add(nPhoto);
      pPhoto.setVisible(false);
      nPhoto.setVisible(false);
      
      add(titlePanel);
      add(picturePanel);
      add(messagePanel);
      add(buttonPanel);
      createMenus();
    }
    
    protected void loadFile(String fileName)
    {
        pictureLabel.setIcon(new ImageIcon(fileName));
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
        pAlbum = new Album();
        frame.getContentPane().add(pAlbum);
        frame.pack();
        frame.setVisible(true);
       
    }
    
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
                //pAlbum.openAlbum();
            break;
            case 2:
                System.exit(0);
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
    
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    private void initComponents() {//GEN-BEGIN:initComponents
        
        setLayout(new java.awt.BorderLayout());
        
    }//GEN-END:initComponents


    // Variables declaration - do not modify//GEN-BEGIN:variables
    // End of variables declaration//GEN-END:variables

}
