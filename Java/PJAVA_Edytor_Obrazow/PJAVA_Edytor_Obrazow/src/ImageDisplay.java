import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

/**
 * The ImageDisplay class provides functionality to load, display,
 * manipulate, and save images. It also supports mouse-based image cutting.
 * @author Błażej Marciniak, Igor Popławski
 */
public class ImageDisplay implements MouseListener, MouseMotionListener {
    private ImageModifier image = null; // The object that holds and modifies the image
    private final ImagePanel view; // The panel used to display the image
    private boolean cut1 = true; // Flag to indicate the first point selection in cutting
    private boolean cut2 = false; // Flag to indicate the second point selection in cutting
    private boolean startcut = false; // Flag to indicate if cutting is enabled
    private boolean acceptcut = false; // Flag to indicate if cutting is complete
    private int x1; // X-coordinate of the first point for cutting
    private int y1; // Y-coordinate of the first point for cutting
    private int width; // Width of the cutting rectangle
    private int height; // Height of the cutting rectangle
    private int lcx; // X-coordinate of the top-left corner of the cutting rectangle
    private int lcy; // Y-coordinate of the top-left corner of the cutting rectangle

    /**
     * Constructor initializes the view and adds mouse listeners.
     */
    public ImageDisplay() {
        view = new ImagePanel();
        view.addMouseListener(this);
        view.addMouseMotionListener(this);
    }

    /**
     * Gets the JPanel containing the image.
     *
     * @return the view panel
     */
    public JPanel getView() {
        return view;
    }

    /**
     * Gets the current image being displayed.
     *
     * @return the ImageModifier object or null if no image is set
     */
    public ImageModifier getImage() {
        if (image != null) {
            return image;
        }
        return null;
    }

    /**
     * Sets the image to be displayed and initializes the ImageModifier.
     *
     * @param image the BufferedImage to set
     */
    public void setImage(BufferedImage image) {
        this.image = new ImageModifier(image);
        view.setImage(image);
    }

    /**
     * Updates the view with a given image without modifying the current image object.
     *
     * @param image the BufferedImage to display
     */
    public void setView(BufferedImage image) {
        view.setImage(image);
    }

    /**
     * Loads an image from a file and displays it.
     *
     * @param file the file containing the image
     * @throws IOException if the image cannot be read
     */
    public void loadImage(File file) throws IOException {
        BufferedImage loadedImage = ImageIO.read(file);
        image = new ImageModifier(loadedImage);
        view.setImage(image);
    }

    /**
     * Saves the current image to a file.
     *
     * @param file the file to save the image to
     * @throws IOException if the image cannot be written
     */
    public void saveImage(File file) throws IOException {
        if (image != null) {
            ImageIO.write(image.getImage(), "png", file);
        }
    }

    /**
     * Gets the current state of the acceptcut flag.
     *
     * @return true if cutting is complete, false otherwise
     */
    public boolean getacceptcut() {
        return acceptcut;
    }

    /**
     * Resets the cutting process flags to their initial states.
     */
    public void resetcut() {
        this.acceptcut = false;
        this.startcut = false;
        this.cut1 = true;
        this.cut2 = false;
    }

    /**
     * Enables or disables the startcut flag.
     *
     * @param startCut true to enable cutting, false to disable
     */
    public void setStartCut(boolean startCut) {
        this.startcut = startCut;
    }

    /**
     * Cuts a portion of the image based on selected coordinates and updates the view.
     */
    public void cutImage() {
        BufferedImage subImage = image.getSubimage(lcx, lcy, width, height);
        setImage(subImage);
        acceptcut = false;
        startcut = false;
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        Point p = view.getImageCoordinates(e.getX(), e.getY());

        if (cut1 && startcut) {
            // First click sets the first point for the cutting rectangle
            x1 = p.x;
            y1 = p.y;
            cut2 = true;
            cut1 = false;
        } else if (cut2) {
            // Second click sets the second point and calculates the rectangle
            int x2 = p.x;
            int y2 = p.y;

            if (x1 > x2 && y1 > y2) {
                lcx = x2;
                lcy = y2;
                width = x1 - x2;
                height = y1 - y2;
            } else {
                lcx = x1;
                lcy = y1;
                width = x2 - x1;
                height = y2 - y1;
            }
            acceptcut = true;

            // Preview the selected area with a black mask
            ImageModifier preview = new ImageModifier(image);
            setView(preview.applyBlackMask(image.getWidth(), image.getHeight(), lcx, lcy, width, height));
            cut2 = false;
            cut1 = true;
        }
    }

    @Override
    public void mousePressed(MouseEvent e) {
    }

    @Override
    public void mouseReleased(MouseEvent e) {
    }

    @Override
    public void mouseEntered(MouseEvent e) {
    }

    @Override
    public void mouseExited(MouseEvent e) {
    }

    @Override
    public void mouseDragged(MouseEvent e) {
    }

    @Override
    public void mouseMoved(MouseEvent e) {
    }
}