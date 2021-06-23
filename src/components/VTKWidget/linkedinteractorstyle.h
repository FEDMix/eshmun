#ifndef LINKEDINTERACTIONSTYLE_H
#define LINKEDINTERACTIONSTYLE_H

#include <vtkInteractorStyleImage.h>
#include <vector>

class SceneWidget;

/** Interactor style that enables synchronization of properties like
 *  window/level, slice position, cursors, between SceneWidgets.
 *  Use SetBaseWidget to set the SceneWidget it is being used in as an
 *  actual interactor style,
 *  and AddLinkedWidget to link to other SceneWidgets.
 */
class LinkedInteractorStyle : public vtkInteractorStyleImage {

public:
    static LinkedInteractorStyle* New();
    vtkTypeMacro(LinkedInteractorStyle, vtkInteractorStyleImage);

    LinkedInteractorStyle();
    ~LinkedInteractorStyle();

    virtual void WindowLevel() override;
    virtual void OnMouseWheelForward() override;
    virtual void OnMouseWheelBackward() override;
    virtual void OnKeyDown() override;
    virtual void SetBaseWidget(SceneWidget* sceneWidget);
    virtual void AddLinkedWidget(SceneWidget* sceneWidget);
protected:
    void MoveSliceForward();
    void MoveSliceBackward();
private:
    std::vector<SceneWidget*> linkedWidgets;
    SceneWidget* baseWidget;
};

#endif // LINKEDINTERACTIONSTYLE_H
