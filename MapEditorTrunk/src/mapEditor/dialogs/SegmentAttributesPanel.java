package mapEditor.dialogs;

import java.awt.Graphics;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;


import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class SegmentAttributesPanel extends JPanel implements WindowListener{
	private static ImageIcon img = new ImageIcon();
	
	private JFrame M_Frame;

	public SegmentAttributesPanel() {
//		System.out.println(img);
		M_Frame = new JFrame();
		
		GridBagLayout gridbag = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();
		M_Frame.getContentPane().setLayout(gridbag);
		c.fill = GridBagConstraints.BOTH;
		c.weightx=1.0;//proporcje powi�kszania si�
		c.weighty=1.0;//proporcje powi�kszania si�	
		c.gridx = 0;
        c.gridy = 0;
        gridbag.setConstraints(this, c);
 	
        M_Frame.getContentPane().add(this);
        //M_Frame.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        M_Frame.setSize(400,400);
        M_Frame.addWindowListener(this);
        //M_Frame.setVisible(true);
	//	System.out.println(M_Frame);
	
	}
	
	@Override
	public void setVisible(boolean p_vis){
//		System.out.println("wid "+this.M_Frame);
		this.M_Frame.setVisible(true);	
	}
	
	@Override
	public void paint(Graphics g){
	
		g.setPaintMode();
//		g.drawLine(0,0,10,10);
		g.drawImage(img.getImage(),0,0,
		getSize().width/2, getSize().height/2,
		getBackground(), this);

//		super.paint(g);	 - nie u�ywa� bo nic si� nie b�dzie malowa�o
	}
	public static void main (String[] args){
		SegmentAttributesPanel SAT = new SegmentAttributesPanel();
		SAT.setVisible(false);
	}

	public void windowOpened(WindowEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("windowOpened okno atrybut�w");
	}

	public void windowClosing(WindowEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("windowClosing okno atrybut�w");
	}

	public void windowClosed(WindowEvent arg0) {
		System.out.println("windowClosed okno atrybut�w");
		
	}

	public void windowIconified(WindowEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("windowIconified okno atrybut�w");
	}

	public void windowDeiconified(WindowEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("windowDeiconified okno atrybut�w");
	}

	public void windowActivated(WindowEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("windowActivated okno atrybut�w");
	}

	public void windowDeactivated(WindowEvent arg0) {
		// TODO Auto-generated method stub
		System.out.println("windowDeactivated okno atrybut�w");
	}
}

