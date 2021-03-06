/*
 * Album.java
 *
 * Created on February 25, 2002, 10:10 PM
 */

//package Album;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import javax.swing.event.*;
import javax.swing.border.BevelBorder;
import ExampleFileFilter;
import java.io.File;
import java.io.BufferedReader;
import java.io.FileReader;
import java.beans.*;
import java.awt.MediaTracker;
/**
 *
 * @author  Mark Salisbury
 */
public class Album extends javax.swing.JPanel {

    class AboutDialog extends JDialog {
        private JOptionPane optionPane;

        public AboutDialog() {
            super(frame, true);

            setTitle("About Photo Album");
            setSize(300,200);
            String m1, m2, m3;
               
            m1 = new String("Photo Album Program");
            m2 = new String("Written for CS 5100 2/6/2002");
            m3 = new String("by Mark Salisbury");
                                  
            Object[] array = {m1,m2,m3};        
            final String btnString1 = "OK";
            
            Object[] options = {btnString1};

            optionPane = new JOptionPane(array, 
                                        JOptionPane.INFORMATION_MESSAGE,
                                        JOptionPane.OK_OPTION ,
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
                        optionPane.setValue(new Integer(
                                            JOptionPane.CLOSED_OPTION));
                }
            });
                  
            optionPane.addPropertyChangeListener(new PropertyChangeListener() {
                public void propertyChange(PropertyChangeEvent e) 
                {
                    setVisible(false);
                }}
            );
        }
    }
    
    class AlbumFiles extends JFrame
    {
        public AlbumFiles()
        {
            
            getContentPane().setLayout(null);
            JTextArea message = new JTextArea("Album files containing N photos require 2N + 1 lines.  The first line is a single integer number representing the number of photos in the album.  The following lines alternate between the filename of a GIF or JPG format photo and a caption describing the photo.  The format for filenames is either relative or absolute.  Relative filename paths are interpreted relative to the directory containing the album file.");
            message.setLineWrap(true);
            message.setWrapStyleWord(true);
            message.setBackground(Color.lightGray);
            
            getContentPane().add(message);
            message.setBounds(10,10,220,200);
            JButton closeButton = new JButton("OK");
            closeButton.addActionListener(new buttonListener());
            getContentPane().add(closeButton);
            closeButton.setBounds(70,210,80,30);
            setTitle("About Album Files");
            setSize(245,275);
            setVisible(true);            
        }
    }
     
     class Progress extends JFrame
     {
        public JLabel progressLabel;
        private JProgressBar pBar; 
        public void SetProgress(int value)
        {
            pBar.setValue(value);
        }
        public Progress(String message)
        {
            
            getContentPane().setLayout(null);
            progressLabel = new JLabel(message);
            pBar = new JProgressBar(0,100);
            
            getContentPane().add(progressLabel);
            progressLabel.setBounds(10,10,230,40);
            getContentPane().add(pBar);
            pBar.setBounds(10,50,230,70);
            
            setSize(240,80);
            setTitle("Loading Images...");
            setVisible(true);            
        }
    }
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
    private String albumDirectory;
    private AlbumFiles aFiles;
    private JPopupMenu popup;
    private boolean popupVisible = false;
    private int viewingMode = 0; // 0 = no album loaded
                                 // 1 = album loaded, normal window
                                 // 2 = album loaded, full screen mode
    private int scaleMode = 0;
    private int indicatorType = 1;
    private Image Images[];
    private Image ScaledImages[];
    
    public void openAlbum()
    {
        //Create a file chooser
        final JFileChooser fc = new JFileChooser();
        
        ExampleFileFilter filter = new ExampleFileFilter(new String("alb"), "Album Files");
        //filter.addExtenstion(new String("jpg"));
        fc.addChoosableFileFilter(filter);
        String currentDir = System.getProperty("user.dir");
        fc.setCurrentDirectory(new File(currentDir));
        
        //In response to a button click:
        int returnVal = fc.showOpenDialog(this);
        
        if(returnVal == JFileChooser.APPROVE_OPTION)
        {
            currentDir = fc.getCurrentDirectory().toString();
            albumDirectory = currentDir;
            System.setProperty("user.dir",currentDir);
            
            albumTitle = fc.getSelectedFile().getName();
            
            try 
            {
                BufferedReader in = new BufferedReader(new FileReader(fc.getSelectedFile().getPath()));
                popup.removeAll();
                String thisLine;
                thisLine = in.readLine();
                if (thisLine != null)
                {
                    nFiles = Integer.parseInt(thisLine);
                }
                System.out.println("nFiles = "+nFiles);
                fileNames = new String[nFiles];
                fileComments = new String[nFiles];
                PopupMenuItemListener pListener = new PopupMenuItemListener();
                MenuItemListener mListener = new MenuItemListener();
                MyMenuItem mi = new MyMenuItem("Automatic Mode", 5);
                mi.addActionListener(mListener);
                popup.add(mi);
                popup.addSeparator();
                for (int i = 0; i < nFiles; i++)
                {
                    fileNames[i] = in.readLine();
                    System.out.println("fileNames["+i+"] = "+fileNames[i]);
                    fileComments[i] = in.readLine();
                    mi = new MyMenuItem(fileComments[i], i);
                    mi.addActionListener(pListener);
                    popup.add(mi);
                    System.out.println("fileComments["+i+"] = "+fileComments[i]);
                }
                LoadImages();
                ScaleImages(500,500);
            }
            catch (Exception e) 
            {
                e.printStackTrace();
            }
            
        }   
    }
    
    public void LoadImages()
    {
        Images = new Image[nFiles];
        String fileName;
        
        messageLabel.setText("Loading Album...");
        
        if (indicatorType == 0)
        {
            frame.setCursor(new java.awt.Cursor(java.awt.Cursor.WAIT_CURSOR));
        }
        
        for (int i = 0; i < nFiles; i++)
        {
            if (fileNames[i].charAt(1)==':')
              fileName = fileNames[i];
            else 
              fileName = albumDirectory + "\\" + fileNames[i];
            Images[i] = Toolkit.getDefaultToolkit().getImage(fileName);
        }
        
        if (indicatorType == 0)
        {
            frame.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        }
    }
    
    class IObserver implements java.awt.image.ImageObserver
    {
        public boolean imageUpdate(java.awt.Image image, int infoflags, int x, int y, int width, int height) 
        {
            //messageLabel.setText("Loading image "+(currentFileIndex+1)+" of "+nFiles+", "+(height * 100 / 500)+"% complete");
            System.out.println("IObserver: currentFileIndex = "+currentFileIndex+", height = "+height+"y="+y);
            return (height >= 500);
        }   
    }
    
    class LoadListener implements ActionListener
    {
        
        public void actionPerformed(java.awt.event.ActionEvent actionEvent) 
        {
                
            for (currentFileIndex = 0; currentFileIndex < nFiles; currentFileIndex++)
            {
                Toolkit.getDefaultToolkit().prepareImage(ScaledImages[currentFileIndex], -1, -1, new IObserver());
            }    
           
            if (indicatorType == 0)
            {
                frame.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
            }
            setViewingMode(1);
            startDisplay();
        }
    }
    
    public void ScaleImages(int width, int height)
    {
        ScaledImages = new Image[nFiles];
        messageLabel.setText("Scaling Images...");
        
        if (indicatorType == 0)
        {
            frame.setCursor(new java.awt.Cursor(java.awt.Cursor.WAIT_CURSOR));
        }
        int hints;
        if (scaleMode == 0)
        {
            hints = Image.SCALE_AREA_AVERAGING;
        }
        else
        {
            hints = Image.SCALE_REPLICATE;
        }
        MediaTracker tracker = new MediaTracker(frame);
        for (int i = 0; i < nFiles; i++)
        {
            ScaledImages[i] = Images[i].getScaledInstance(width,height,hints);
            tracker.addImage(ScaledImages[i],i);
        }
        if (indicatorType == 2)
        {
            Progress PBar = new Progress("Loading Image 1");
        }
        for (currentFileIndex = 0; currentFileIndex < nFiles; currentFileIndex++)
        {
            try
            {
                while (tracker.waitForID(currentFileIndex,100)==false)
                {
                    height = ScaledImages[currentFileIndex].getHeight( new IObserver());
                    int pComplete = (height * 100 / 500);
                    String message = "Loading image "+(currentFileIndex+1)+" of "+nFiles+" "+pComplete+"% complete";
                    if (indicatorType == 2)
                    {
                        PBar.SetValue(pComplete);
                        PBar.ProgressLabel.setText(message);
                        PBar.paint(PBar.getGraphics());
                    }
                    else
                    {
                        messageLabel.setText(message);
                    }
                    System.out.println("ScaleImages: currentFileIndex = "+currentFileIndex+", height = "+height);
                    frame.paint(frame.getGraphics());
                    
                }
                //frame.prepareImage(ScaledImages[currentFileIndex], new IObserver());
            }
            catch(Exception e)
            {
                
            }
        }
        if (indicatorType == 0)
        {
            frame.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        }
        setViewingMode(1);
        startDisplay();
        
    }
    
    private void startDisplay()
    {
        startMode = true;    
        titleLabel.setText(albumTitle);
        messageLabel.setText("");
        pPhoto.setVisible(false);
        nPhoto.setText("Start");
        nPhoto.setVisible(true);
        nPhoto.setEnabled(true);
        pictureLabel.setIcon(null);
        currentFileIndex = 0;
    }
    
    private void setViewingMode(int mode)
    {
        if (mode == 0 || viewingMode == mode)
            return;
        
        if (mode == 2)
        {
            // going to full-screen
            
        }
        else if (mode == 1)
        {
           // closing full-screen   
            
        }
        viewingMode = mode;
    }
    
    private void setDisplay()
    {
        pPhoto.setEnabled(currentFileIndex > 0);
        nPhoto.setEnabled(currentFileIndex < nFiles - 1);
        titleLabel.setText(albumTitle + " image " + (currentFileIndex + 1) + " of " + nFiles + " (" + fileNames[currentFileIndex] + ")");
        messageLabel.setText(fileComments[currentFileIndex]);
        
        //ImageIcon image = new ImageIcon(Toolkit.getDefaultToolkit().getImage(fileName).getScaledInstance(500,500,Image.SCALE_DEFAULT));//fileName);
        //ImageIcon image = new ImageIcon(Images[currentFileIndex].getScaledInstance(500,500,Image.SCALE_DEFAULT));//fileName);
        ImageIcon image = new ImageIcon(ScaledImages[currentFileIndex]);//fileName);
        
        //image.loadImage();
        //Image i = ;
        pictureLabel.setIcon(image);
        
        //pictureLabel.setBounds(0,0,500,500);
        //pictureLabel.setIcon(image);
        //Image i = new Image(
        //pictureLabel.setBounds(4,4,500,500);
        //pictureLabel.prepareImage(image,500,500,new ImageObserver());
        //pictureLabel.prepareImage(i,frame);
        //pictureLabel.paintImmediately(0,0,500,500);
    }
    
    public class buttonListener implements ActionListener
    {
        public void actionPerformed(java.awt.event.ActionEvent actionEvent)
        {
            JButton button = (JButton)actionEvent.getSource();
            if (button.getText().compareTo(new String("Previous Photo"))==0)
            {
                System.out.println("Previous Photo");
                pAlbum.previousButton();
            }
            else if (button.getText().compareTo(new String("OK"))==0)
            {
                aFiles.setVisible(false);
            }
            else
            {
                if (startMode == true)
                {
                    currentFileIndex = 0;
                    startMode = false;
                    pPhoto.setVisible(true);
                    nPhoto.setText("Next Photo");
                    setDisplay();
                }
                else 
                {
                    pAlbum.nextButton();
                }
                System.out.println("Next Photo");
            }
        }
    }
     
    class MyKeyListener implements KeyListener
    {
        public void keyPressed(KeyEvent e)
        {
            if (viewingMode == 2)
            {
                pAlbum.setViewingMode(1);
            }
            
            //System.out.println("Key pressed...");
            int a = e.getModifiers();
            int b = e.getKeyCode();
            System.out.println("a="+a+"b="+b);
            if (a==2 && b == 65)
            {
                AboutDialog dDlg = new AboutDialog();
                dDlg.setVisible(true);
            }
            else if (a==2 && b == 70)
            {
                aFiles = new AlbumFiles();
            }
            if (a==2 && b == 79)
            {
                // call open
                pAlbum.openAlbum();
            }
            else if(a == 2 && b == 88)
            {
                System.exit(0);
            }
            if (viewingMode != 0)
            {
                if (a==0 && b==37)
                {
                    //left
                    pAlbum.previousButton();
                }
                if (a==0 && b==39)
                {
                    //right
                    pAlbum.nextButton();
                }
            }
        }
        
        public void keyReleased(java.awt.event.KeyEvent keyEvent) {
        }
        
        public void keyTyped(java.awt.event.KeyEvent keyEvent) {
        }
        
    }
        
    
    class PopupMenuMonitor implements PopupMenuListener
    {
        public void popupMenuCanceled(javax.swing.event.PopupMenuEvent popupMenuEvent) {
        }
        
        public void popupMenuWillBecomeInvisible(javax.swing.event.PopupMenuEvent popupMenuEvent) {
        }
        
        public void popupMenuWillBecomeVisible(javax.swing.event.PopupMenuEvent popupMenuEvent) {
        }
        
    }
    
    protected void create()
    {
      popup = new JPopupMenu("Popup Menu");
      popup.setLabel("Popup Menu");
      
      popup.setInvoker(frame);
      popup.addPopupMenuListener(new PopupMenuMonitor());
      MouseListener mL = new MouseAdapter()
      {
        public void mouseClicked(MouseEvent e)
        {
            popupVisible = !popupVisible;
            if (popupVisible)
            {
                popup.show(frame,e.getX(),e.getY());
            }
            else
            {
                popup.setVisible(false);
            }
        }
      };  
      frame.addMouseListener(mL);
      add(popup);
      
      frame.addKeyListener(new MyKeyListener());
      //setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
      setLayout(null);
      titlePanel = new JPanel();
      titleLabel = new JLabel("Photo Album Program - No Album Loaded");
      titlePanel.add(titleLabel);
      titlePanel.setBounds(0,0,500,30);
      
      picturePanel = new JPanel();
      picturePanel.setLayout(null);
      picturePanel.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
      
      pictureLabel = new JLabel();
      pictureLabel.setSize(500,500);
      //pictureLabel.setMaximumSize(new Dimension(500,500));
      //pictureLabel.setPreferredSize(new Dimension(500,500));
      //pictureLabel.setMinimumSize(new Dimension(500,500));
      picturePanel.add(pictureLabel);
      pictureLabel.setBounds(4,4,500,500);
      picturePanel.setBounds(0,30,508,508);
      
      messagePanel = new JPanel();
      messageLabel = new JLabel("No Image Loaded - Choose Open from the File Menu");
      messagePanel.add(messageLabel);
      messagePanel.setBounds(0,540,500,30);
      
      buttonPanel = new JPanel();
      pPhoto = new JButton("Previous Photo");
      pPhoto.addActionListener(new buttonListener());
      nPhoto = new JButton("Next Photo");
      nPhoto.addActionListener(new buttonListener());
      buttonPanel.add(pPhoto);
      pPhoto.setBounds(191,0,120,30);
      nPhoto.setBounds(318,0,100,30);
      buttonPanel.add(nPhoto);
      pPhoto.setVisible(false);
      nPhoto.setVisible(false);
      buttonPanel.setBounds(0,570,500,35);
      
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
        return new Dimension(512,608);
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
    
    public void previousButton()
    {
        if (currentFileIndex > 0)
        {
            currentFileIndex--;
            setDisplay();
        }
    }
    
    public void nextButton()
    {
        if (currentFileIndex < nFiles - 1)
        {
            currentFileIndex++;
            setDisplay();
        }
    }
    
    private void createMenus()
    {
        JMenu fileMenu = new JMenu("File");
        fileMenu.setMnemonic('F');
        MyMenuItem mi11 = new MyMenuItem("Open Album (Ctrl+O)",1);
        
        //mi11.setAccelerator(new KeyStroke('O',java.awt.Event.CTRL_MASK));
        
        MenuItemListener miListener = new MenuItemListener();
        mi11.addActionListener(miListener);
        MyMenuItem mi12 = new MyMenuItem("Exit (Ctrl+X)",2);
        mi12.addActionListener(miListener);
        fileMenu.add(mi11);
        fileMenu.addSeparator();
        fileMenu.add(mi12);

        RadioMenuItemListener rbListener = new RadioMenuItemListener();
        JMenu scalingMenu = new JMenu("Scales");  //  average, replicate
        scalingMenu.setMnemonic('S');
        MyRadioButtonItem rbmi1 = new MyRadioButtonItem("Average",true,1);
        MyRadioButtonItem rbmi2 = new MyRadioButtonItem("Replicate",false,2);
        rbmi1.addActionListener(rbListener);
        rbmi2.addActionListener(rbListener);
        ButtonGroup bg1 = new ButtonGroup();
        bg1.add(rbmi1);
        bg1.add(rbmi2);
        scalingMenu.add(rbmi1);
        scalingMenu.add(rbmi2);
        
        JMenu trackingMenu = new JMenu("Tracking"); // cursor, label, progress bar
        trackingMenu.setMnemonic('T');
        rbmi1 = new MyRadioButtonItem("Cursor",false,3);
        rbmi2 = new MyRadioButtonItem("Label",true,4);
        MyRadioButtonItem rbmi3 = new MyRadioButtonItem("Progress Bar",false,5);
        rbmi1.addActionListener(rbListener);
        rbmi2.addActionListener(rbListener);
        rbmi3.addActionListener(rbListener);
        ButtonGroup bg2 = new ButtonGroup();
        bg2.add(rbmi1);
        bg2.add(rbmi2);
        bg2.add(rbmi3);
        trackingMenu.add(rbmi1);
        trackingMenu.add(rbmi2);
        trackingMenu.add(rbmi3);
        
        JMenu optionsMenu = new JMenu("Help");
        optionsMenu.setMnemonic('H');
        MyMenuItem mi21 = new MyMenuItem("About (Ctrl+A)...",3);
        mi21.addActionListener(miListener);
        MyMenuItem mi22 = new MyMenuItem("Album Files (Ctrl+F)...",4);
        mi22.addActionListener(miListener);

        optionsMenu.add(mi21);
        optionsMenu.add(mi22);

        JMenuBar menuBar = new JMenuBar();
        menuBar.add(fileMenu);
        menuBar.add(scalingMenu);
        menuBar.add(trackingMenu);
        menuBar.add(optionsMenu);
        frame.setJMenuBar(menuBar);
    }
    
    class PopupMenuItemListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            if (viewingMode == 2)
            {
                pAlbum.setViewingMode(1);
                return;
            }
            
            if (viewingMode == 1)
            {
                currentFileIndex = ((MyMenuItem)e.getSource()).id;
                pAlbum.setDisplay();
            }
        }
    }
    class MenuItemListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            switch (((MyMenuItem)e.getSource()).id)
            {
            case 1:
                pAlbum.openAlbum();
            break;
            case 2:
                System.exit(0);
            break;
            case 3:
                AboutDialog dDlg = new AboutDialog();
                dDlg.setVisible(true);
            break;
            case 4:
                aFiles = new AlbumFiles();
            break;
            case 5: //Automatic Mode
                System.exit(0);
            break;
            }
        }
    }
    class RadioMenuItemListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            switch (((MyRadioButtonItem)e.getSource()).id)
            {
            case 1:
                scaleMode = 0;
            break;
            case 2:
                scaleMode = 1;
            break;
            case 3:
                indicatorType = 0;
            break;
            case 4:
                indicatorType = 1;
            break;
            case 5: 
                indicatorType = 2;
            break;
            }
            System.out.println("scaleMode="+scaleMode);
            System.out.println("indicatorType="+indicatorType);
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
    class MyRadioButtonItem extends JRadioButtonMenuItem
    {
        public int id;
        public MyRadioButtonItem(String name, boolean isSelected, int Id)
        {
            super(name, isSelected);
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
