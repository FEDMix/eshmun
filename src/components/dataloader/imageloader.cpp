#include "imageloader.h"

QString ImageLoader::image_scan(QString path) {
    // Use OS dependent separator
    QString path_scan = QDir::cleanPath(path + QDir::separator()
                                        + "scans" + QDir::separator()+ "scan_to_annotate");
    qInfo( "Directory path to scan images: %s", qUtf8Printable(path_scan));
    //std::cout << "path to the scan " + path_scan.toStdString() << endl;
    //std::cout << typeid(path_scan).name() << endl;

    return path_scan;
}

QString ImageLoader::image_annotation(QString path) {
    // Use OS dependent separator
    QString path_annotation = QDir::cleanPath(path + QDir::separator()
                                        + "annotations" + QDir::separator()+ "annotation1");
    qInfo( "Directory path to annotation images: %s", qUtf8Printable(path_annotation));

    return path_annotation;
}




