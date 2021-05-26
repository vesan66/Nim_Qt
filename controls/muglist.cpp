#include "muglist.h"

MugList::MugList(QWidget *parent) : QWidget(parent) {
    this->setGeometry(_startupPosition);
    this->setObjectName("muglist");
    setupUi();
}

void MugList::setupUi() {

    int xEndPos = 0;
    for(int i = 0; i <_count; i++) {
        MugGUI* pMG = new MugGUI(this);
        pMG->SetMyId((i + 1));
        xEndPos = i * (pMG->width() + _spacing);
        pMG->setGeometry(xEndPos, pMG->pos().y(), pMG->width(), pMG->height());
    }
    ClearAllMarksAndHideElements();
}


MugGUI* MugList::GetMugById(const int& id) {
    for(auto item:this->children() ) {
        if (typeid(*item) == typeid(MugGUI)) {
            MugGUI* rd = dynamic_cast<MugGUI* const>(item);
            if (rd->MyId() == id){
                return rd;
            }
        }
    }
    return nullptr;
}


void MugList::ClearAllMarksAndHideElements() {
    for(auto item:this->children() ) {
        if (typeid(*item) == typeid(MugGUI)) {
            MugGUI* rd = dynamic_cast<MugGUI* const>(item);
            rd->ClearMarks();
            rd->SetBtnVisible(false, 0);
        }
    }
}

void MugList::SetMugs(const CMugs &cm) {

    if (cm.size() == 0) {return;}

    for (const CMug& mug : cm) {
        MugGUI* pMugGui = this->GetMugById(mug.number);
        if (pMugGui != nullptr) {
            for (auto pearl : mug.pearls) {
                if (pearl.number != -1){
                    pMugGui->SetBtnVisible(true, pearl.number);
                }
            }
            if(mug.choosen != 0) {
                pMugGui->SetBtnVisible(true, mug.choosen);
                pMugGui->SetMark(mug.choosen);
            }

        }
    }
}

