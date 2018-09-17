#include "ClickDetector.h"


void ClickDetector::update() {

	for (auto&& target : targets) {
		for (const auto& pointer : pointers) {
			Clickable& tgt = *target.lock();
			Pointer& ptr = *pointer.lock();

			if (tgt.contains(ptr.getPos()))
			{
				//�}�E�X�I�[�o�[����
				if (!tgt.mouseOver) {
					tgt.mouseOver = true;
					tgt.onMouseOver();
				}
				//�N���b�N����
				if (ptr.isClicked()) {
					tgt.onClick();
					break;
				}
			} 
			else if (tgt.mouseOver) {
				tgt.mouseOver = false;
				tgt.onMouseOut();
			}
		}
	}
}