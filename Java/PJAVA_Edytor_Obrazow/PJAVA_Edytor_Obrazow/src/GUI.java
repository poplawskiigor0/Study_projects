import javax.swing.*;
import java.awt.*;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;

/**
 * GUI class to represent the graphical user interface for the multimedia application.
 * Manages the main JFrame, ImageDisplay, and Buttons components.
 * @author Błażej Marciniak, Igor Popławski
 */
public class GUI {
    private final JFrame frame;
    private final ImageDisplay imageDisplay;
    private final Buttons buttons;

    /**
     * Constructor to initialize and configure the graphical user interface.
     */
    public GUI() {
        frame = new JFrame("Aplikacja multimedialna w języku Java");
        frame.getContentPane().setBackground(Color.decode("#222222"));
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(null);
        frame.setSize(1200, 850);
        frame.setExtendedState(JFrame.MAXIMIZED_BOTH);

        imageDisplay = new ImageDisplay();
        buttons = new Buttons(imageDisplay);
        imageDisplay.getView().setBackground(Color.decode("#222222"));
        buttons.setBackground(Color.decode("#222222"));

        frame.add(imageDisplay.getView());
        frame.add(buttons);

        buttons.setBounds(0, frame.getHeight() - 100, frame.getWidth(), 100);
        imageDisplay.getView().setBounds(0, 0, frame.getWidth(), frame.getHeight() - 100);

        frame.addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent e) {
                int frameWidth = frame.getWidth();
                int frameHeight = frame.getHeight();

                buttons.setBounds(0, frameHeight - 120, frameWidth, 100);

                imageDisplay.getView().setBounds(0, 0, frameWidth, frameHeight - 120);

                buttons.revalidate();
                imageDisplay.getView().revalidate();
                frame.repaint();
            }
        });

        frame.setVisible(true);
    }
}
