import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

/**
 * ImagePanel is a custom JPanel designed to display a scaled image while
 * maintaining its aspect ratio. It also provides functionality to map
 * panel coordinates to image coordinates.
 * @author Błażej Marciniak, Igor Popławski
 */
public class ImagePanel extends JPanel {
    private BufferedImage image; // The image to be displayed on the panel

    /**
     * Sets a new image to be displayed and refreshes the panel.
     *
     * @param image the BufferedImage to display
     */
    public void setImage(BufferedImage image) {
        this.image = image;
        repaint(); // Refresh the panel to draw the new image
    }

    /**
     * Paints the image on the panel, scaling it to fit while maintaining the aspect ratio.
     *
     * @param g the Graphics object used for drawing
     */
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        if (image != null) {
            int panelWidth = getWidth(); // Width of the panel
            int panelHeight = getHeight(); // Height of the panel

            // Calculate the aspect ratios of the image and the panel
            double imgAspect = (double) image.getWidth() / image.getHeight();
            double panelAspect = (double) panelWidth / panelHeight;

            int newWidth, newHeight;

            if (imgAspect > panelAspect) {
                // If the image is wider than the panel, scale to fit the width
                newWidth = panelWidth;
                newHeight = (int) (panelWidth / imgAspect);
            } else {
                // If the image is taller than the panel, scale to fit the height
                newWidth = (int) (panelHeight * imgAspect);
                newHeight = panelHeight;
            }

            // Center the scaled image within the panel
            int x = (panelWidth - newWidth) / 2;
            int y = (panelHeight - newHeight) / 2;

            // Draw the image
            g.drawImage(image, x, y, newWidth, newHeight, this);
        }
    }

    /**
     * Maps panel coordinates to image coordinates, considering the scaling and centering of the image.
     *
     * @param panelX the x-coordinate on the panel
     * @param panelY the y-coordinate on the panel
     * @return a Point representing the corresponding coordinates on the image, or null if the coordinates are outside the image
     */
    public Point getImageCoordinates(int panelX, int panelY) {
        if (image == null) {
            return null; // No image is loaded, so no coordinates can be mapped
        }

        int panelWidth = getWidth(); // Width of the panel
        int panelHeight = getHeight(); // Height of the panel

        // Calculate the aspect ratios of the image and the panel
        double imgAspect = (double) image.getWidth() / image.getHeight();
        double panelAspect = (double) panelWidth / panelHeight;

        int xOffset = 0, yOffset = 0;
        int displayedWidth, displayedHeight;

        if (imgAspect > panelAspect) {
            // If the image is wider than the panel, it is scaled to fit the width
            displayedWidth = panelWidth;
            displayedHeight = (int) (panelWidth / imgAspect);
            yOffset = (panelHeight - displayedHeight) / 2; // Center the image vertically
        } else {
            // If the image is taller than the panel, it is scaled to fit the height
            displayedWidth = (int) (panelHeight * imgAspect);
            displayedHeight = panelHeight;
            xOffset = (panelWidth - displayedWidth) / 2; // Center the image horizontally
        }

        // Check if the panel coordinates are outside the displayed image area
        if (panelX < xOffset || panelX > xOffset + displayedWidth || panelY < yOffset || panelY > yOffset + displayedHeight) {
            return null; // The click is outside the image area
        }

        // Map panel coordinates to image coordinates using the scaling ratio
        int imageX = (int) ((panelX - xOffset) * (double) image.getWidth() / displayedWidth);
        int imageY = (int) ((panelY - yOffset) * (double) image.getHeight() / displayedHeight);

        return new Point(imageX, imageY); // Return the mapped image coordinates
    }
}