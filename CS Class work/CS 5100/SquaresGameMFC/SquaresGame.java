/*
 * JFrame.java
 *
 * Created on January 25, 2002, 12:10 AM
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.JOptionPane;
import javax.swing.JDialog;
import java.beans.*;// this is for the property change listeners in the dialog\
import javax.swing.JColorChooser;
/**
 *
 * @author  Mark Salisbury
 */
public class SquaresGame extends javax.swing.JFrame
{
    int xBox;
    int yBox;
    final int squareSize = 60;
    final int lineWidth = 5;
    public Color lineColor = new Color(100,100,100);
    final Color emptySquareColor = new Color(150,150,150);
    final Color emptySideColor = new Color(150,150,150);
    public Color playerColor[] = new Color[2];
    static int bestScores[] = new int[5];
    static String bestNames[] = {new String(),new String(),new String(),new String(),new String()};
    static int bestScoreCount = 0;
    
    int totalSquaresLeft;
    int currentPlayer = 0;
    int pScoreValue[] = new int[2];

    int gameType = 0; // 0 = 2-player, 1= simple opponent, 2= challenging opponent
    GamePanel gPanel;
    static SquaresGame sGame;
    ComputerPlayer computer;

    class NewGameDialog extends JDialog {
        //public String sizeText = null;
        public int gameSize;
        public int gameType;
        private JOptionPane optionPane;
        private JTextField size;
        private JRadioButton rb1;
        private JRadioButton rb2;
        private JRadioButton rb3;
        public boolean cancelled = true;
        public NewGameDialog() {
            super(sGame, true);

            setTitle("Select Game Options");
            setSize(400,300);
            
            JLabel sizeLabel = new JLabel(" Size of game field (3-10)");
            sizeLabel.setSize(50,30);
            size = new JTextField("3");    
          
            rb1 = new JRadioButton("2 player game");
            rb2 = new JRadioButton("Easy computer opponent");
            rb3 = new JRadioButton("Hard computer opponent");
            rb1.setSelected(true);
            ButtonGroup bg = new ButtonGroup();
            bg.add(rb1);
            bg.add(rb2);
            bg.add(rb3);
            
            Object[] array = {sizeLabel, size, rb1,rb2,rb3};        
            final String btnString1 = "OK";
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
                        optionPane.setValue(new Integer(
                                            JOptionPane.CLOSED_OPTION));
                }
            });

            //size.addActionListener(new ActionListener() {
            //    public void actionPerformed(ActionEvent e) {
            //        optionPane.setValue(btnString1);
            //    }
            //});

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

                        if (value.equals(btnString1)) {
                            // pressed ok
                            boolean validated = false;
                            try 
                            {
                               gameSize = Integer.parseInt(size.getText());
                               if (gameSize < 3 || gameSize > 10)
                               {
                                   JOptionPane.showMessageDialog(
                                                NewGameDialog.this,
                                                "Sorry, \"" + size.getText() + "\" "
                                                + "isn't a valid response.\n"
                                                + "Please enter a number from 3-10.",
                                                "Try again",
                                                JOptionPane.ERROR_MESSAGE);
                               }
                               else
                                   validated = true;
                            }
                            catch (NumberFormatException f)
                            {
                                JOptionPane.showMessageDialog(
                                                NewGameDialog.this,
                                                "Sorry, \"" + size.getText() + "\" "
                                                + "isn't a valid response.\n"
                                                + "Please enter a number from 3-10.",
                                                "Try again",
                                                JOptionPane.ERROR_MESSAGE);
                            }
                            if (rb1.isSelected())
                            {
                                gameType = 0;
                            }
                            else if (rb2.isSelected())
                            {
                                gameType = 1;
                            }
                            else if (rb3.isSelected())
                            {
                                gameType = 2;
                            }
                            else
                            {
                                validated = false;
                                JOptionPane.showMessageDialog(
                                                NewGameDialog.this,
                                                "Please select the type of game you want to play.",
                                                "Try again",
                                                JOptionPane.ERROR_MESSAGE);
                            }
                            if (validated)
                            {
                                cancelled = false;
                                setVisible(false);
                            }
         
                        } else { // user closed dialog or clicked cancel
                           
                            setVisible(false);
                        }
                    }
                }
            });
        }
    }
    
    class ChangeSizeDialog extends JDialog {
        //public String sizeText = null;
        public int gameSize;
        private JOptionPane optionPane;
        private JTextField size;
        public boolean cancelled = true;
        public ChangeSizeDialog() {
            super(sGame, true);

            setTitle("Select Game Size");
            setSize(400,300);
            
            JLabel sizeLabel = new JLabel(" Size of game field (3-10)");
            sizeLabel.setSize(50,30);
            size = new JTextField("3");    
                      
            Object[] array = {sizeLabel, size};        
            final String btnString1 = "OK";
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
                        optionPane.setValue(new Integer(
                                            JOptionPane.CLOSED_OPTION));
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

                        if (value.equals(btnString1)) {
                            // pressed ok
                            boolean validated = false;
                            try 
                            {
                               gameSize = Integer.parseInt(size.getText());
                               if (gameSize < 3 || gameSize > 10)
                               {
                                   JOptionPane.showMessageDialog(
                                                ChangeSizeDialog.this,
                                                "Sorry, \"" + size.getText() + "\" "
                                                + "isn't a valid response.\n"
                                                + "Please enter a number from 3-10.",
                                                "Try again",
                                                JOptionPane.ERROR_MESSAGE);
                               }
                               else
                                   validated = true;
                            }
                            catch (NumberFormatException f)
                            {
                                JOptionPane.showMessageDialog(
                                                ChangeSizeDialog.this,
                                                "Sorry, \"" + size.getText() + "\" "
                                                + "isn't a valid response.\n"
                                                + "Please enter a number from 3-10.",
                                                "Try again",
                                                JOptionPane.ERROR_MESSAGE);
                            }
                           
                            if (validated)
                            {
                                cancelled = false;
                                setVisible(false);
                            }
         
                        } else { // user closed dialog or clicked cancel
                           
                            setVisible(false);
                        }
                    }
                }
            });
        }
    }
    
    class GameOverDialog extends JDialog {
        private JOptionPane optionPane;

        public GameOverDialog(String victorName, int percent, boolean isTie) {
            super(sGame, true);

            setTitle("Game Over");
            setSize(300,200);
            String m1, m2, m3;
            if (isTie)
            {    
                m1 = new String("The game is over.");
                m2 = new String("The game is a tie");
                m3 = new String("");
            }
            else
            {
                m1 = new String("The game is over.");
                m2 = new String(victorName+ " is the victor!");
                m3 = new String(victorName+" has captured "+percent+"% of the squares.");
            }
                      
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
    
    class BestScoresDialog extends JDialog {
        private JOptionPane optionPane;

        public BestScoresDialog() {
            super(sGame, true);

            setTitle("Best Scores");
            setSize(300,250);
            String array[] = new String[bestScoreCount+1];
            if (bestScoreCount == 0)
                array[0] = new String("There are no best scores yet.");
            else
            {
                array[0] = new String("The best scores are:");
                for (int i = 0; i < bestScoreCount; i++)
                {
                    array[i+1]= new String(i+1+". "+bestNames[i]+" "+bestScores[i]+"%");
                }
            }
               
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
    /*
    public class NewGameDialog extends JDialog
    {
      public NewGameDialog()
      {
          super(sGame,true);
          dialogInit();
          createRootPane();

          CreateDialog();
      }
      
      private void CreateDialog()
      {
          JPanel dlgPanel = new JPanel();
          getContentPane().setLayout(null);
          dlgPanel.setLayout(null);
          
          JLabel sizeLabel = new JLabel(" Size of game field (3-10)");
          
          JTextField size = new JTextField("3");    
          
          JRadioButton rb1 = new JRadioButton("2 player game");
          JRadioButton rb2 = new JRadioButton("Easy computer opponent");
          JRadioButton rb3 = new JRadioButton("Hard computer opponent");
          
          ButtonGroup bg = new ButtonGroup();
          bg.add(rb1);
          bg.add(rb2);
          bg.add(rb3);
          
          
          dlgPanel.add(sizeLabel);
          
          dlgPanel.add(size);
          dlgPanel.add(rb1);
          dlgPanel.add(rb2);
          dlgPanel.add(rb3);
          sizeLabel.setLocation(20,20);
          size.setLocation(80,20);
          rb1.setLocation(40,50);
          rb2.setLocation(40,80);
          rb3.setLocation(40,110);
          //getContentPane().setSize(120,150);
           
          dlgPanel.setSize(200,150);
          dlgPanel.setVisible(true);
          setSize(200,150);
          getContentPane().add(dlgPanel);
      }
        
    }
    */
    public class Side extends JButton
    {
        public class listener implements ActionListener
        {

            public void actionPerformed(java.awt.event.ActionEvent actionEvent)
            {
                Side s = (Side)actionEvent.getSource();
                s.setBackground(lineColor);
                s.setEnabled(false);
                set = 1;
                notifySquares();
            }

        }

        public int set = 0;
        private Square s1 = null;
        private Square s2 = null;

        public Side()
        {
            this.addActionListener(new listener());
            setBorderPainted(false);
            setBackground(emptySideColor);
            this.setCursor(java.awt.Cursor.getPredefinedCursor(HAND_CURSOR));
        }
        public void refreshColors()
        {
          if (set != 0)
              setBackground(lineColor);
        }
        public void AddSquare(Square s)
        {
            if (s1 == null)
            {
                s1 = s;
            }
            else if (s2 == null)
            {
                s2 = s;
            }
        }

        public boolean trySide()
        {
          if (set == 0)
          {
            if (s1.getSidesFilled() < 2)
            { 
              if (s2 != null)
              { 
                if (s2.getSidesFilled() < 2)
                {
                  doClick();
                  return true;
                }
                else
                  return false;
              }
              else
              {
                doClick();
                return true;
              }
            }
            else
              return false;
          }
          else
            return false;
        }

        private void notifySquares()
        {
          boolean squareCompleted = false;
          squareCompleted = s1.check();
          if (s2 != null)
          {
              squareCompleted = s2.check() || squareCompleted;
          }
          boolean computerTurn = false;
          if (squareCompleted == false)
          // if the last move did not result in a square
          // being completly filled, then it is someone else's turn.
          {
              sGame.gPanel.sPanel.pLabel[currentPlayer].setForeground(new Color(150, 180, 220));
              currentPlayer = (currentPlayer + 1) % 2;
              sGame.gPanel.sPanel.pLabel[currentPlayer].setForeground(new Color(0,0,0));
              if (gameType != 0 && currentPlayer != 0)
              {
                // computer's turn to make a move...
                  computerTurn = true;
              }
          }
          if (squareCompleted == true && gameType != 0 && currentPlayer != 0)
          {
             // computer's turn to make a move...
             computerTurn = true;
          }
          if (computerTurn)
          {
             //try {
             //  java.lang.Thread.sleep(1000);
             //}
             //catch (InterruptedException e)
             //{
             //    
             //}
             computer.MakeMove();   
          }
        }
    }
    public class Square extends JButton
    {
        private Side Top;
        private Side Bottom;
        private Side Left;
        private Side Right;
        private boolean isFilled = false;
        private int owner = -1;
        
        public Side getRightSide()
        {
            return Right;
        }

        public Side getLeftSide()
        {
            return Left;
        }

        public Side getTopSide()
        {
            return Top;
        }

        public Side getBottomSide()
        {
            return Bottom;
        }
        public int getSidesFilled()
        {
          return Left.set + Right.set + Top.set + Bottom.set;
        }
        public Side getEmptySide()
        {
           if (Top.set == 0)
             return Top;
           else if (Left.set == 0)
             return Left;
           else if (Bottom.set == 0)
             return Bottom;
           else if (Right.set == 0)
             return Right;
           else
             return null;
        }
        public boolean trySquare()
        {
          if (Left.trySide())
          {
            return true;
          }
          if (Right.trySide())
          {
            return true;
          }
          if (Top.trySide())
          {
            return true;
          }
          if (Bottom.trySide())
          {
            return true;
          }
          return false;
        }
        public void refreshColors()
        {
            if (owner != -1)
            {
                setBackground(playerColor[owner]);
            }
            Left.refreshColors();
            Top.refreshColors();
            Bottom.refreshColors();
            Right.refreshColors();
        }
        public boolean check()
        {
          if (getSidesFilled() == 4 && isFilled == false)
          {
              totalSquaresLeft--;
              System.out.println("squares left = "+totalSquaresLeft);
              isFilled = true;
              // change someone's score now
              // color me...
              owner = currentPlayer;
              setBackground(playerColor[currentPlayer]);
              pScoreValue[currentPlayer]++;
              sGame.gPanel.sPanel.pScore[currentPlayer].setText(" " + String.valueOf(pScoreValue[currentPlayer]));
              if (totalSquaresLeft == 0)
              {
                //.. the game is over... 
                  int percent = 50;
                  String name = new String("");
                  GameOverDialog gDlg;
                  boolean isTie = false;
                if (pScoreValue[0] > pScoreValue[1])
                {
                    name = new String(sGame.gPanel.sPanel.pLabel[0].getText());
                    percent = pScoreValue[0] * 100 /(pScoreValue[0]+pScoreValue[1]);
                    gDlg = new GameOverDialog(name,percent,false);
                    
                }
                else if (pScoreValue[1] > pScoreValue[0])
                {
                    name = new String(sGame.gPanel.sPanel.pLabel[1].getText());
                    percent = pScoreValue[1] * 100 /(pScoreValue[0]+pScoreValue[1]);
                    gDlg = new GameOverDialog(name,percent,false);
                }
                else
                {
                    gDlg = new GameOverDialog(null,50,true);
                    isTie = true;
                }
                gDlg.setVisible(true);
                if (isTie == false)
                {
                    if (submitBestScore(percent,name))
                    {
                        BestScoresDialog bDlg = new BestScoresDialog();
                        bDlg.setVisible(true);
                    }
                }
                
              }
              return true;
          }
          return false;
        }

        Square(int x, int y, SquaresPanel gamePanel)
        {
            //.. always create a bottom and a right side
            Insets insets = gamePanel.getInsets();

            if (x == 0)
            {
                // create a left side
                Left = new Side();
                gamePanel.add(Left);
                Left.setBounds(x * squareSize /*+ insets.left*/, y * squareSize + lineWidth /*+ insets.top*/, lineWidth, squareSize - lineWidth);
            }
            else
            {
                Left = gamePanel.getSquare(x - 1, y).getRightSide();
            }
            Left.AddSquare(this);

            if (y == 0)
            {
                // create a top side
                Top = new Side();
                gamePanel.add(Top);
                Top.setBounds(x * squareSize + lineWidth /*+ insets.left*/, y * squareSize /*+ insets.top*/, squareSize - lineWidth, lineWidth);
            }
            else
            {
                Top = gamePanel.getSquare(x, y - 1).getBottomSide();
            }
            Top.AddSquare(this);

            Right = new Side();
            gamePanel.add(Right);
            Right.AddSquare(this);
            Right.setBounds((x+1) * squareSize /*+ insets.left*/, y * squareSize + lineWidth/* + insets.top*/, lineWidth, squareSize - lineWidth);

            Bottom = new Side();
            gamePanel.add(Bottom);
            Bottom.AddSquare(this);
            Bottom.setBounds(x * squareSize + lineWidth /*+ insets.left*/, (y+1) * squareSize /*+ insets.top*/, squareSize - lineWidth, lineWidth);

            setBorderPainted(false);
            setEnabled(false);
            setBackground(emptySquareColor);
        }
    }
    public class ComputerPlayer
    {
      public ComputerPlayer()
      {

      }
      public void MakeMove()
      {

      }
    }

    public class EasyComputer extends ComputerPlayer
    {
      Square asquares[];
      private int squaresLeft = 0;
      public EasyComputer()
      {
        squaresLeft = xBox * yBox;
        asquares = new Square[xBox * yBox];
        //System.out.println(sGame.toString());
        //System.out.println(sGame.gPanel.toString());
        //System.out.println(sGame.gPanel.bottomPanel.toString());

        for (int i = 0; i < xBox; i++)
        {
          for (int j = 0; j < yBox; j++)
          {
            asquares[i*yBox+j] = sGame.gPanel.bottomPanel.getSquare(i,j);
          }
        }

      }
      public void MakeMove()
      {
        while (squaresLeft > 0)
        {
          int squareIndex = (int)((double)squaresLeft*java.lang.Math.random());
          System.out.println("squaresLeft="+squaresLeft+" squareIndex="+squareIndex+" sidesFilled="+asquares[squareIndex].getSidesFilled());
          if (asquares[squareIndex].getSidesFilled() < 4)
          {
            if (asquares[squareIndex].getTopSide().set == 0)
            {
              asquares[squareIndex].getTopSide().doClick();
              return;
            }
            else if (asquares[squareIndex].getBottomSide().set == 0)
            {
              asquares[squareIndex].getBottomSide().doClick();
              return;
            }
            else if (asquares[squareIndex].getLeftSide().set == 0)
            {
              asquares[squareIndex].getLeftSide().doClick();
              return;
            }
            else if (asquares[squareIndex].getRightSide().set == 0)
            {
              asquares[squareIndex].getRightSide().doClick();
              return;
            }
            else
            {
              System.out.println("Error: getSidesFilled() < 4 and all sides are set");
            }
          }
          else
          {
            squaresLeft--;
            Square tempSquare;
            tempSquare = asquares[squareIndex];
            asquares[squareIndex] = asquares[squaresLeft];
            asquares[squaresLeft] = tempSquare;
          }
        }
        //System.out.println("no blank squares found");
      }
    }

    public class HardComputer extends ComputerPlayer
    {
        Square aSquares[];
        Square eSquares[];
        private int aSquaresLeft = 0;
        private int eSquaresLeft = 0;

        public HardComputer()
        {
            aSquaresLeft = xBox * yBox;
            eSquaresLeft = xBox * yBox;
            aSquares = new Square[xBox * yBox];
            eSquares = new Square[xBox * yBox];

            for (int i = 0; i < xBox; i++)
            {
              for (int j = 0; j < yBox; j++)
              {
                aSquares[i*yBox+j] = eSquares[i*yBox+j] = sGame.gPanel.bottomPanel.getSquare(i,j);
              }
            }
        }
        public void MakeMove()
        {
            // 'available' squares are those squares which are not completely filled in
            // 'empty' squares are those which have fewer than two sides filled

            // first, look for a square which has 3 sides filled in.
            for (int i = aSquaresLeft - 1; i >= 0; i--)
            {
               if (aSquares[i].getSidesFilled()== 3)
               {
                 aSquares[i].getEmptySide().doClick();
                 return;
               }
               else if (aSquares[i].getSidesFilled()==4)
               {
                 aSquaresLeft--;
                 Square tempSquare;
                 tempSquare = aSquares[i];
                 aSquares[i] = aSquares[aSquaresLeft];
                 aSquares[aSquaresLeft] = tempSquare;
               }
            }
            
            // now try and find a square which will not cause the other player to get a square
            int esIndex[] = new int[eSquaresLeft];
            for (int i = 0; i < eSquaresLeft; i++)
            {
              esIndex[i] = i;
            }
            
            for (int i = eSquaresLeft - 1; i >= 0; i--)
            {
              // select one of the indexes at random, then check it so see if its square has a candidate side
              int rIndex = (int)((double)i*java.lang.Math.random());              
              int squareIndex = esIndex[rIndex];

              //System.out.println("squaresLeft="+squaresLeft+" squareIndex="+squareIndex);
              boolean squareIsGood = false;
              if (eSquares[squareIndex].getSidesFilled() < 2)
              {
                if (eSquares[squareIndex].trySquare())
                  squareIsGood = true;
              }

              if (!squareIsGood)
              {
                 eSquaresLeft--;
                 Square tempSquare;
                 tempSquare = eSquares[squareIndex];
                 eSquares[squareIndex] = eSquares[eSquaresLeft];
                 eSquares[eSquaresLeft] = tempSquare;
              }
              else
                return;
              esIndex[rIndex] = esIndex[i]; // so that we don't choose the same e square index again 
            }
            // now just look for the first available move
            for (int i = aSquaresLeft - 1; i >= 0; i--)
            {
               if (aSquares[i].getSidesFilled() < 4)
               {
                 aSquares[i].getEmptySide().doClick();
                 return;
               }
            }

        }// end of function MakeMove
    }// end of class HardComputer

    public class ScorePanel extends JPanel
    {
        public JTextField pScore[];
        public JLabel pLabel[];
        public ScorePanel(int gType)
        {
            pLabel = new JLabel[2];
            pLabel[0] = new JLabel(" Player 1 ");
            if (gType == 0)
              pLabel[1] = new JLabel(" Player 2 ");
            else
              pLabel[1] = new JLabel(" Opponent ");
            pScore = new JTextField[2];
            pScore[0] = new JTextField("  0  ");
            pScore[0].setSize(30,60);
            pScore[1] = new JTextField("  0   ");
            pScore[1].setSize(30,60);
            pScore[0].setEditable(false);
            pScore[1].setEditable(false);
            add(pLabel[0]);
            add(pScore[0]);
            add(pLabel[1]);
            add(pScore[1]);
            this.setBackground(new Color(230,240,255));
            pLabel[0].setForeground(new Color(0,0,0));
            pLabel[1].setForeground(new Color(150, 180, 220));
            //JRadioButton rb1 = new JRadioButton("score panel");
            //add(rb1);
        }
    }
    public class SquaresPanel extends JPanel
    {
        private int xsquares = 3;
        private int ysquares = 3;
        Square squares[][];

        public SquaresPanel(int xs, int ys)
        {
            setLayout(null);
            this.setBackground(lineColor);
            squares = new Square[xs][ys];
            xsquares = xs;
            ysquares = ys;

            for (int i = 0; i < xs; i++)
            {
                for (int j = 0; j < ys; j++)
                {
                    squares[i][j] = new Square(i, j, this);
                    add(squares[i][j]);
                    squares[i][j].setBounds(i * squareSize + lineWidth + 1, j * squareSize + lineWidth + 1, squareSize - lineWidth - 2, squareSize - lineWidth - 2);
                }
            }
            pack();
            //JRadioButton rb1 = new JRadioButton("squares panel");
            //add(rb1);
        }
        public void destroy()
        {
          for (int i = 0; i < xsquares; i++)
            {
                for (int j = 0; j < ysquares; j++)
                {
                    squares[i][j] = null;
                }
            }
            this.removeAll();
        }

        public Square getSquare(int x, int y)
        {
            return squares[x][y];
        }
        public void refreshColors()
        {
            for (int i = 0; i < xsquares; i++)
            {
                for (int j = 0; j < ysquares; j++)
                {
                    squares[i][j].refreshColors();
                }
            }
        }
        
    }

    public class GamePanel extends JPanel
    {
        ScorePanel sPanel;
        SquaresPanel bottomPanel;
        public GamePanel(int xs, int ys, int gType)
        {
            sPanel = new ScorePanel(gType);
            bottomPanel = new SquaresPanel(xs,ys);
            //setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
            setLayout(null);
               //this.setMaximumSize(new Dimension(3 * squareSize + 10,
               //                   2 * squareSize + 10));
              //  this.setMaximumSize(new Dimension(xs * squareSize + 10,
              //                    ys * squareSize + 10));
            sPanel.setBounds(0,0,xs * squareSize + lineWidth, 55);
            bottomPanel.setBounds(0,55,xs * squareSize + 10, ys * squareSize + lineWidth + 15);
            setBounds(0,0,xs*squareSize + lineWidth, (ys + 1) * squareSize + lineWidth + 15);
            add(sPanel, BorderLayout.NORTH);
            add(bottomPanel, BorderLayout.NORTH);
            pack();
        }
        public void refreshColors()
        {
          bottomPanel.refreshColors();
          //sPanel.refreshColors();
        }
        public void destroy()
        {
          sPanel.removeAll();
          sPanel = null;
          bottomPanel.destroy();
          bottomPanel = null;
          this.removeAll();
        }
    }
    /** Creates new form JFrame */

    class MenuItemListener implements ActionListener
    {
      public void actionPerformed(ActionEvent e)
      {
        Color color;
        switch (((MyMenuItem)e.getSource()).id)
        {
        case 1:
        CreateNewSquaresGame();
        //System.out.println("option 1");
        break;
        case 2:
        //System.out.println("option 2");
            BestScoresDialog bDlg = new BestScoresDialog();
            bDlg.setVisible(true);
        break;
        case 3:
        System.exit(0);
        //System.out.println("option 3");
        break;
        case 4:
            color = JColorChooser.showDialog(sGame,
                                 "Choose Player 1 Color",
                                 sGame.playerColor[0]);
            if (color != null)
            {
                sGame.playerColor[0] = color;
                sGame.refreshColors();
            }
        break;
        case 5: 
            color = JColorChooser.showDialog(sGame,
                                 "Choose Player 2 Color",
                                 sGame.playerColor[1]);
            if (color != null)
            {
                sGame.playerColor[1] = color;
                sGame.refreshColors();
            }
        break;
        case 6:
            color = JColorChooser.showDialog(sGame,
                                 "Choose Line Color",
                                 sGame.lineColor);
            if (color != null)
            {
                sGame.lineColor = color;
                sGame.refreshColors();
            }
        //System.out.println("option 4");
        break;
        case 7:
        {
            ChangeSizeDialog csDialog = new ChangeSizeDialog();
            csDialog.setVisible(true);
            if (csDialog.cancelled == true)
                return;
            DoChangeSize(csDialog.gameSize,sGame.gameType);
        }
        //System.out.println("option 5");
        break;
        }

      }
    }

    public void ChangeSize(int gameSize, int gType)
    {
        xBox = gameSize;
        yBox = gameSize;
        gameType = gType;
        InitializeGame();
    }
    
    public void CreateGame()
    {
        NewGameDialog ngDialog = new NewGameDialog();
        ngDialog.setVisible(true);
        if (ngDialog.cancelled == true)
        {
            System.exit(0);
            return;
        }
        sGame.xBox = ngDialog.gameSize;
        sGame.yBox = ngDialog.gameSize;
        sGame.gameType = ngDialog.gameType;
        InitializeGame();
    }

    public void InitializeGame()
    {
         pScoreValue[0] = 0;
      pScoreValue[1] = 0;
      currentPlayer = 0;
      if (gPanel != null)
      {
        gPanel.destroy();
        getContentPane().remove(gPanel);
        gPanel = null;
        this.pack();
      }
      totalSquaresLeft = xBox * yBox;
      gPanel = new GamePanel(xBox,yBox,gameType);
      //getContentPane().setLayout(new BorderLayout());
      getContentPane().add(gPanel);
      if (gameType == 0)
        computer = null;
      else if (gameType == 1)
        computer = new EasyComputer();
      else if (gameType == 2)
        computer = new HardComputer();
      this.setSize(xBox * squareSize+lineWidth+8, yBox * squareSize + lineWidth + 105);
      setVisible(true);
    }
    
    public void refreshColors()
    {
        gPanel.refreshColors();
    }
    public SquaresGame()
    {
        initComponents();
        setTitle("Squares Game");
        playerColor[0] = new Color(0,255,0);
        playerColor[1] = new Color(0,0,255);
        getContentPane().setLayout(null);
        createMenus();
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

    private void createMenus()
    {
        JMenu fileMenu = new JMenu("File");
        MyMenuItem mi11 = new MyMenuItem("New Game...",1);
        MenuItemListener miListener = new MenuItemListener();
        mi11.addActionListener(miListener);
        MyMenuItem mi12 = new MyMenuItem("Best Game...",2);
        mi12.addActionListener(miListener);
        MyMenuItem mi13 = new MyMenuItem("Exit",3);
        mi13.addActionListener(miListener);
        fileMenu.add(mi11);
        fileMenu.add(mi12);
        fileMenu.addSeparator();
        fileMenu.add(mi13);

        JMenu optionsMenu = new JMenu("Options");
        JMenu mi21 = new JMenu("Colors");//new MyMenuItem("Colors",4);
        MyMenuItem p1Color = new MyMenuItem("Player 1 Color",4);
        p1Color.addActionListener(miListener);
        MyMenuItem p2Color = new MyMenuItem("Player 2 Color",5);
        p2Color.addActionListener(miListener);
        MyMenuItem lColor = new MyMenuItem("Line Color",6);
        lColor.addActionListener(miListener);
        mi21.add(p1Color);
        mi21.add(p2Color);
        mi21.add(lColor);
        MyMenuItem mi22 = new MyMenuItem("Pick Size...",7);
        mi22.addActionListener(miListener);

        optionsMenu.add(mi21);
        optionsMenu.add(mi22);

        JMenuBar menuBar = new JMenuBar();
        menuBar.add(fileMenu);
        menuBar.add(optionsMenu);
        setJMenuBar(menuBar);


    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    private void initComponents() {//GEN-BEGIN:initComponents
        addWindowListener(new java.awt.event.WindowAdapter() {
                              public void windowClosing(java.awt.event.WindowEvent evt) {
                                  exitForm(evt);
                              }
                          }
                         );
        pack();
    }//GEN-END:initComponents

    /** Exit the Application */
    private void exitForm(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_exitForm
        System.exit(0);
    }//GEN-LAST:event_exitForm

    /**
    * @param args the command line arguments
    */
    public static void DoChangeSize(int gameSize, int gameType)
    {
       if (sGame != null)
       {
           sGame.setVisible(false);
           sGame = null;
       }
       sGame = new SquaresGame();
       sGame.ChangeSize(gameSize,gameType);
        
    }
    
    public static boolean submitBestScore(int score, String name)
    {
        for (int i = 0; i < 5; i++)
        {
            if (i >= bestScoreCount || score > bestScores[i])
            {
              for (int j = 4; j > i; j--)
              {
                bestScores[j] = bestScores[j - 1];
                bestNames[j] = bestNames[j - 1];
              }
              bestScores[i] = score;
              bestNames[i] = name;
              if (bestScoreCount < 5)
                bestScoreCount++;
              return true;
            }
        }
       return false;
    }
    
    public static void CreateNewSquaresGame()
    {
       if (sGame != null)
       {
           sGame.setVisible(false);
           sGame = null;
       }
       sGame = new SquaresGame();
       sGame.CreateGame();
    }
    
    public static void main(String args[]) 
    {
        CreateNewSquaresGame();
    }


    // Variables declaration - do not modify//GEN-BEGIN:variables
    // End of variables declaration//GEN-END:variables

}


