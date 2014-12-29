package mapeditor.dialogs;

import java.awt.Graphics;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class SegmentAttributesPanel extends JPanel {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private static ImageIcon img = new ImageIcon();

	private JFrame M_Frame;
	private SegmentAttributesWindowListener saWindowListener;

	public SegmentAttributesPanel() {
		M_Frame = new JFrame();

		GridBagLayout gridbag = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();
		M_Frame.getContentPane().setLayout(gridbag);
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;// proporcje powiekszania
		c.weighty = 1.0;// proporcje powiekszania
		c.gridx = 0;
		c.gridy = 0;
		gridbag.setConstraints(this, c);

		M_Frame.getContentPane().add(this);
		// M_Frame.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		M_Frame.setSize(400, 400);
		saWindowListener = new SegmentAttributesWindowListener();
		M_Frame.addWindowListener(saWindowListener);
		// M_Frame.setVisible(true);
		// System.out.println(M_Frame);

	}

	@Override
	public void setVisible(boolean p_vis) {
		this.M_Frame.setVisible(true);
	}

	@Override
	public void paint(Graphics g) {

		g.setPaintMode();
		// g.drawLine(0,0,10,10);
		g.drawImage(img.getImage(), 0, 0, getSize().width / 2,
				getSize().height / 2, getBackground(), this);

		// super.paint(g); - nie u�ywa� bo nic si� nie b�dzie malowa�o
	}

	public static void main(String[] args) {
		SegmentAttributesPanel SAT = new SegmentAttributesPanel();
		SAT.setVisible(false);
	}

}
