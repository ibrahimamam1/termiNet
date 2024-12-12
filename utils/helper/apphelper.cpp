#include "apphelper.h"
#include <QPainter>
#include <QPainterPath>

AppHelper::AppHelper() {}

QImage AppHelper::createRoundedIcon(const QImage& sourceImage, int diameter) {
    if (sourceImage.isNull()) {
        return QImage();
    }

    // Scale the image while maintaining aspect ratio
    QImage scaledImage = sourceImage.scaled(diameter, diameter, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Create a new image with an alpha channel
    QImage roundedImage(diameter, diameter, QImage::Format_ARGB32_Premultiplied);
    roundedImage.fill(Qt::transparent);

    // Create a painter to draw on the image
    QPainter painter(&roundedImage);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // Create a circular clipping path
    QPainterPath path;
    path.addEllipse(0, 0, diameter, diameter);
    painter.setClipPath(path);

    // Draw the scaled image
    painter.drawImage(0, 0, scaledImage);

    return roundedImage;
}
