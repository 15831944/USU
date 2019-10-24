/*
 * JFrame.java
 *
 * Created on January 25, 2002, 12:10 AM
 */

package SquaresGame;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 *
 * @author  Mark Salisbury
 */
public class SquaresGame extends javax.swing.JFrame 
{
    final int xBox = 3;
    final int yBox = 3;
    final int squareSize = 40;
    final int lineWidth = 5;
    final Color lineColor = new Color(100,100,100);
    final Color emptySquareColor = new Color(150,150,150);
    final Color emptySideColor = new Color(150,150,150);
    Color playerColor[] = new Color[2];
    
    int currentPlayer = 0;
    int pScoreValue[] = new int[2];
    ScorePanel sPanel;
    
    public class ScorePanel extends JPanel
    {
        public JTextField pScore[];
        public JLabel pLabel[];
        public ScorePanel()
        {
            pLabel = new JLabel[2];
            pLabel[0] = new JLabel(" Player 1 ");
            pLabel[1] = new JLabel(" Player 2 ");
            pScore = new JTextField[2];
            pScore[0] = new JTextField(" 0");
            pScore[1] = new JTextField(" 0");
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
        
    public class GamePanel extends JPanel
    {
        public class SquaresPanel extends JPanel
        {
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
                    this.setCursor(new Cursor(HAND_CURSOR));
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
                
                private void notifySquares()
                {
                  boolean squareCompleted = false;
                  squareCompleted = s1.check();
                  if (s2 != null)
                  {
                      squareCompleted = s2.check() || squareCompleted;
                  }
                  if (squareCompleted == false)
                  {
                      sPanel.pLabel[currentPlayer].setForeground(new Color(150, 180, 220));
                      currentPlayer = (currentPlayer + 1) % 2;
                      sPanel.pLabel[currentPlayer].setForeground(new Color(0,0,0));
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
                
                public boolean check()
                {
                  int SidesSet = Left.set + Right.set + Top.set + Bottom.set;
                  if (SidesSet == 4 && isFilled == false)
                  {
                      isFilled = true;
                      // change someone's score now
                      // color me...    
                      setBackground(playerColor[currentPlayer]);
                      pScoreValue[currentPlayer]++;
                      sPanel.pScore[currentPlayer].setText(" " + String.valueOf(pScoreValue[currentPlayer]));
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
            
            public Square getSquare(int x, int y)
            {
                return squares[x][y];
                
            }
        }
        
        public GamePanel(int xs, int ys)
        {
            sPanel = new ScorePanel();
            SquaresPanel bottomPanel = new SquaresPanel(xs,ys);
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
    }       
    /** Creates new form JFrame */
    public SquaresGame() {
        initComponents();
        playerColor[0] = new Color(0,255,0);
        playerColor[1] = new Color(0,0,255);
        GamePanel gPanel = new GamePanel(xBox,yBox);
        //getContentPane().setLayout(new BorderLayout());
        getContentPane().setLayout(null);
        getContentPane().add(gPanel);
        this.setSize(xBox * squareSize+lineWidth+8, yBox * squareSize + lineWidth + 90);
        
        
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
    public static void main(String args[]) {
        
        SquaresGame sGame = new SquaresGame();
        //sGame.pack();
        sGame.setVisible(true);
        //new SquaresGame().show();
    }


    // Variables declaration - do not modify//GEN-BEGIN:variables
    // End of variables declaration//GEN-END:variables

}
