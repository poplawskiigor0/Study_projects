import javax.swing.*;
import java.awt.*;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.awt.image.ColorModel;
import java.awt.image.WritableRaster;


/**
 * ImageModifier extends BufferedImage to provide advanced image modification
 * functionalities, such as rotation, color transformations, flipping, and masking.
 * @author Błażej Marciniak, Igor Popławski
 */
public class ImageModifier extends BufferedImage {

    /**
     * Constructs an ImageModifier object by copying the contents of the given BufferedImage.
     *
     * @param img the BufferedImage to copy
     */
    public ImageModifier(BufferedImage img) {
        super(img.getWidth(), img.getHeight(), img.getType());
        this.copyImg(img);
    }

    /**
     * Returns the current image.
     *
     * @return the BufferedImage object
     */
    public BufferedImage getImage() {
        return this;
    }

    /**
     * Creates a deep copy of the current image, ensuring modifications do not affect the original.
     *
     * @return a deep-copied BufferedImage
     */
    public BufferedImage deepCopyImage() {
        ColorModel colorModel = this.getColorModel();
        boolean isAlphaPremultiplied = colorModel.isAlphaPremultiplied();
        WritableRaster raster = this.copyData(null);
        return new BufferedImage(colorModel, raster, isAlphaPremultiplied, null);
    }

    /**
     * Rotates the image by a user-specified angle.
     *
     * @return the rotated and cropped BufferedImage
     * @throws IllegalArgumentException if the input angle is invalid
     */
    public BufferedImage rotate() throws IllegalArgumentException{
        String inputValue = JOptionPane.showInputDialog(null,
                "Wprowadź wartość kąta do obrotu:",
                "Wprowadź dane",
                JOptionPane.QUESTION_MESSAGE);
        double angle = Double.parseDouble(inputValue);

        int width = this.getWidth();
        int height = this.getHeight();
        double radians = Math.toRadians(angle);

        int newWidth = (int) Math.abs(width * Math.cos(radians)) + (int) Math.abs(height * Math.sin(radians));
        int newHeight = (int) Math.abs(width * Math.sin(radians)) + (int) Math.abs(height * Math.cos(radians));

        BufferedImage rotatedImage = new BufferedImage(newWidth, newHeight, BufferedImage.TYPE_INT_ARGB);
        Graphics2D g2d = rotatedImage.createGraphics();

        g2d.setComposite(AlphaComposite.Clear);
        g2d.fillRect(0, 0, newWidth, newHeight);
        g2d.setComposite(AlphaComposite.SrcOver);

        AffineTransform at = new AffineTransform();
        at.translate((newWidth - width) / 2.0, (newHeight - height) / 2.0);
        at.rotate(radians, width / 2.0, height / 2.0);
        g2d.drawRenderedImage(this, at);
        g2d.dispose();

        return cropTransparentBorders(rotatedImage);
    }

    /**
     * Crops transparent borders from a BufferedImage.
     *
     * @param image the image to crop
     * @return the cropped BufferedImage
     */
    private BufferedImage cropTransparentBorders(BufferedImage image) {
        int width = image.getWidth();
        int height = image.getHeight();
        int top, bottom, left, right;

        quit:
        for (top = 0; top < height; top++) {
            for (int x = 0; x < width; x++) {
                if ((image.getRGB(x, top) >> 24) != 0x00) {
                    break quit;
                }
            }
        }

        quit:
        for (bottom = height - 1; bottom > top; bottom--) {
            for (int x = 0; x < width; x++) {
                if ((image.getRGB(x, bottom) >> 24) != 0x00) {
                    break quit;
                }
            }
        }

        quit:
        for (left = 0; left < width; left++) {
            for (int y = top; y <= bottom; y++) {
                if ((image.getRGB(left, y) >> 24) != 0x00) {
                    break quit;
                }
            }
        }

        quit:
        for (right = width - 1; right > left; right--) {
            for (int y = top; y <= bottom; y++) {
                if ((image.getRGB(right, y) >> 24) != 0x00) {
                    break quit;
                }
            }
        }

        int croppedWidth = right - left + 1;
        int croppedHeight = bottom - top + 1;
        return image.getSubimage(left, top, croppedWidth, croppedHeight);
    }

    /**
     * Copies the contents of a BufferedImage into this image.
     *
     * @param img the image to copy
     */
    public void copyImg(BufferedImage img) {
        for (int i = 0; i < img.getWidth(); i++) {
            for (int j = 0; j < img.getHeight(); j++) {
                this.setRGB(i, j, img.getRGB(i, j));
            }
        }
    }

    /**
     * Converts the image to grayscale.
     *
     * @return a new BufferedImage in grayscale
     */
    public BufferedImage greyscale() {
        BufferedImage newImage = deepCopyImage();
        int width = this.getWidth();
        int height = this.getHeight();
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                int color = this.getRGB(i, j);
                int alpha = (color >> 24) & 0xff;
                int blue = color & 0xff;
                int green = (color & 0xff00) >> 8;
                int red = (color & 0xff0000) >> 16;
                if (alpha == 0) {
                    newImage.setRGB(i, j, color);
                    continue;
                }
                int greyscale = Math.max((Math.min(((int)(0.299 * red) + (int)(0.587 * green) + (int)(0.144 * blue)), 255)), 0);
                int newColor = (alpha << 24) | (greyscale << 16) | (greyscale << 8) | greyscale;
                newImage.setRGB(i, j, newColor);
            }
        }
        return newImage;
    }

    /**
     * Converts the image to sepia color palette.
     *
     * @return a new BufferedImage in sepia color palette
     */
    public BufferedImage sepia() {
        BufferedImage newImage = deepCopyImage();
        int width = this.getWidth();
        int height = this.getHeight();

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                int color = this.getRGB(i, j);

                int alpha = (color >> 24) & 0xff;

                int blue = color & 0xff;
                int green = (color >> 8) & 0xff;
                int red = (color >> 16) & 0xff;

                if (alpha == 0) {
                    newImage.setRGB(i, j, color);
                    continue;
                }

                int new_red = Math.min((int)(0.393 * red + 0.769 * green + 0.189 * blue), 255);
                int new_green = Math.min((int)(0.349 * red + 0.686 * green + 0.168 * blue), 255);
                int new_blue = Math.min((int)(0.272 * red + 0.534 * green + 0.131 * blue), 255);

                int newColor = (alpha << 24) | (new_red << 16) | (new_green << 8) | new_blue;

                newImage.setRGB(i, j, newColor);
            }
        }
        return newImage;
    }

    /**
     * Flips the image horizontally
     *
     * @return a new BufferedImage flipped horizontally
     */
    public BufferedImage horizontalFlip() {
        BufferedImage newImage = deepCopyImage();
        int width = this.getWidth();
        int height = this.getHeight();
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                int color = this.getRGB(i, j);
                newImage.setRGB((width - i - 1), j, color);
            }
        }
        return newImage;
    }

    /**
     * Flips the image vertically
     *
     * @return a new BufferedImage flipped vertically
     */
    public BufferedImage verticalFlip() {
        BufferedImage newImage = deepCopyImage();
        int width = this.getWidth();
        int height = this.getHeight();
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                int color = this.getRGB(i, j);
                newImage.setRGB(i, (height - j - 1), color);
            }
        }
        return newImage;
    }

    /**
     * Creates a mask with a specified transparent rectangle on an otherwise opaque black background.
     *
     * @param width      The width of the mask image.
     * @param height     The height of the mask image.
     * @param x          The x-coordinate of the top-left corner of the transparent rectangle.
     * @param y          The y-coordinate of the top-left corner of the transparent rectangle.
     * @param maskWidth  The width of the transparent rectangle.
     * @param maskHeight The height of the transparent rectangle.
     * @return A BufferedImage representing the mask with a transparent rectangle.
     */
    private static BufferedImage createMask(int width, int height, int x, int y, int maskWidth, int maskHeight) {
        BufferedImage mask = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        Graphics2D g2d = mask.createGraphics();

        g2d.setColor(new Color(0, 0, 0, 255));
        g2d.fillRect(0, 0, width, height);

        g2d.setComposite(AlphaComposite.Clear);
        g2d.fillRect(x, y, maskWidth, maskHeight);

        g2d.dispose();
        return mask;
    }

    /**
     * Applies a black mask with a transparent rectangle to the current image.
     *
     * @param width      The width of the mask image.
     * @param height     The height of the mask image.
     * @param x          The x-coordinate of the top-left corner of the transparent rectangle.
     * @param y          The y-coordinate of the top-left corner of the transparent rectangle.
     * @param maskWidth  The width of the transparent rectangle.
     * @param maskHeight The height of the transparent rectangle.
     * @return A BufferedImage of the current image combined with the mask.
     */
    public BufferedImage applyBlackMask(int width, int height, int x, int y, int maskWidth, int maskHeight) {
        BufferedImage mask = createMask(width, height, x, y, maskWidth, maskHeight);
        BufferedImage combined = new BufferedImage(this.getWidth(), this.getHeight(), BufferedImage.TYPE_INT_ARGB);
        Graphics2D g2d = combined.createGraphics();

        g2d.drawImage(this, 0, 0, null);
        g2d.drawImage(mask, 0, 0, null);

        g2d.dispose();
        return combined;
    }
}
