import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

/**
 * A class representing a panel of buttons for image manipulation operations.
 * Implements ActionListener to handle button actions.
 * @author Błażej Marciniak, Igor Popławski
 */
public class Buttons extends JPanel implements ActionListener
{
    private JButton wczytaj, zapisz, skalaSzarosci, sepia, przerzucPoziom, przerzucPion, buttoncut, cancel, buttonrotate;
    private final ImageDisplay imageDisplay;

    /**
     * Constructor initializes the button panel and associates it with the ImageDisplay.
     * @param imageDisplay The ImageDisplay object to interact with.
     */
    public Buttons(ImageDisplay imageDisplay)
    {
        this.imageDisplay = imageDisplay;
        createButtons();
        customizeButtons();
        addButtons();
        addActionListeners();
    }

    /**
     * Creates all the buttons used in the panel.
     */
    public void createButtons()
    {
        wczytaj = new JButton("Wczytaj");
        zapisz = new JButton("Zapisz");
        skalaSzarosci = new JButton("Skala szarosci");
        sepia = new JButton("Sepia");
        przerzucPoziom = new JButton("Poziom");
        przerzucPion = new JButton("Pion");
        buttoncut = new JButton("Cut");
        buttoncut = new JButton("Cut");
        buttonrotate = new JButton();
        cancel = new JButton("Cancel");
    }

    /**
     * Sets the properties for each button, such as size, color, and icons.
     */
    public void customizeButtons()
    {
        wczytaj.setPreferredSize(new Dimension(100, 30));
        wczytaj.setBackground(Color.decode("#26575e"));

        zapisz.setPreferredSize(new Dimension(100, 30));
        zapisz.setBackground(Color.decode("#26575e"));

        skalaSzarosci.setPreferredSize(new Dimension(100, 30));
        skalaSzarosci.setBackground(Color.decode("#26575e"));

        sepia.setPreferredSize(new Dimension(100, 30));
        sepia.setBackground(Color.decode("#26575e"));

        przerzucPoziom.setPreferredSize(new Dimension(100, 30));
        przerzucPoziom.setBackground(Color.decode("#26575e"));

        przerzucPion.setPreferredSize(new Dimension(100, 30));
        przerzucPion.setBackground(Color.decode("#26575e"));

        buttoncut.setPreferredSize(new Dimension(100, 30));
        buttoncut.setBackground(Color.decode("#26575e"));

        buttonrotate.setPreferredSize(new Dimension(100, 30));
        buttonrotate.setBackground(Color.decode("#26575e"));
        ImageIcon rotateicon = new ImageIcon(
                new ImageIcon(getClass().getClassLoader().getResource("rotate.png"))
                        .getImage()
                        .getScaledInstance(30, 30, Image.SCALE_SMOOTH)
        );
        buttonrotate.setIcon(rotateicon);

        cancel.setPreferredSize(new Dimension(100, 30));
        cancel.setBackground(Color.decode("#26575e"));
    }

    /**
     * Adds the buttons to the panel.
     */
    public void addButtons()
    {
        add(wczytaj);
        add(zapisz);
        add(skalaSzarosci);
        add(sepia);
        add(przerzucPoziom);
        add(przerzucPion);
        add(buttonrotate);
        add(buttoncut);
    }

    /**
     * Attaches action listeners to each button to handle user interactions.
     */
    public void addActionListeners()
    {
        wczytaj.addActionListener(this);
        zapisz.addActionListener(this);
        skalaSzarosci.addActionListener(this);
        sepia.addActionListener(this);
        przerzucPoziom.addActionListener(this);
        przerzucPion.addActionListener(this);
        buttoncut.addActionListener(this);
        buttonrotate.addActionListener(this);
        cancel.addActionListener(this);
    }

    /**
     * Resets the cut button to its default state.
     */
    public void resetCutButton()
    {
        buttoncut.setText("Cut");
        imageDisplay.resetcut();
        remove(cancel);
        revalidate();
        repaint();
    }

    /**
     * Handles actions performed by the buttons.
     * @param e The ActionEvent triggered by a button click.
     */
    @Override
    public void actionPerformed(ActionEvent e) {
        Object source = e.getSource();
        try {
            if (source == wczytaj) {
                resetCutButton();
                JFileChooser fileChooser = new JFileChooser();
                if (fileChooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
                    imageDisplay.loadImage(fileChooser.getSelectedFile());
                }
            } else if (source == zapisz) {
                resetCutButton();
                JFileChooser fileChooser = new JFileChooser();
                if (fileChooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
                    File saveFile = fileChooser.getSelectedFile();
                    String fileName = saveFile.getCanonicalPath();
                    if (!fileName.endsWith(".png")) {
                        saveFile = new File(fileName + ".png");
                    }
                    imageDisplay.saveImage(saveFile);
                }
            } else if (source == skalaSzarosci) {
                resetCutButton();
                imageDisplay.setImage(imageDisplay.getImage().greyscale());
            } else if (source == sepia) {
                resetCutButton();
                imageDisplay.setImage(imageDisplay.getImage().sepia());
            } else if (source == przerzucPoziom) {
                resetCutButton();
                imageDisplay.setImage(imageDisplay.getImage().horizontalFlip());
            } else if (source == przerzucPion) {
                resetCutButton();
                imageDisplay.setImage(imageDisplay.getImage().verticalFlip());
            } else if (source == buttoncut) {
                if (imageDisplay.getacceptcut()) {
                    imageDisplay.cutImage();
                    resetCutButton();
                }
                else{
                    imageDisplay.setStartCut(true);
                    buttoncut.setText("Accept");
                    add(cancel);
                    revalidate();
                    repaint();
                }
            } else if (source == buttonrotate) {
                resetCutButton();
                imageDisplay.setImage(imageDisplay.getImage().rotate());
            }else if (source == cancel){
                resetCutButton();
                imageDisplay.setView(imageDisplay.getImage());
                buttoncut.setText("Cut");
                remove(cancel);
                revalidate();
                repaint();
            }
        } catch (IOException ex) {
            System.out.println("Caught exception: " + ex.getMessage());
        } catch (IllegalArgumentException ex) {
            System.out.println("Podano nieprawidłową wartosć (double jest z .): " + ex.getMessage());
        }
    }
}
