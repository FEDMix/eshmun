#ifndef LINKEDINTERACTIONSTYLE_H
#define LINKEDINTERACTIONSTYLE_H

#include <vtkInteractorStyleImage.h>
//#include <vtkTypeMacro.h>
#include <vector>
#include <qwidget.h>

class LinkedInteractorStyle : public vtkInteractorStyleImage {

public:
    static LinkedInteractorStyle* New();
    vtkTypeMacro(LinkedInteractorStyle, vtkInteractorStyleImage);

    LinkedInteractorStyle();
    ~LinkedInteractorStyle();

    virtual void WindowLevel() override;
    virtual void SetBaseWidget(QWidget* sceneWidget);
    virtual void AddLinkedWidget(QWidget* sceneWidget);
private:
    std::vector<QWidget*> linkedWidgets;
    QWidget* baseWidget;
};

#endif // LINKEDINTERACTIONSTYLE_H
