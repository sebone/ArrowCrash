#include "ClickDetector.h"


void ClickDetector::update() {

	for (auto&& target : targets) {
		Clickable& tgt = *target.lock();
		tgt.mouseOverCount = 0;

		for (const auto& pointer : pointers) {
			Pointer& ptr = *pointer.lock();

			if (tgt.contains(ptr.getPos()))
			{
				//�}�E�X�I�[�o�[����
				tgt.mouseOverCount++;
				if (!tgt.mouseOver) tgt.onMouseOver();

				//�N���b�N����
				if (ptr.isClicked()) {
					tgt.onClick();
					break;
				}
			}
		}
		if (tgt.mouseOver && tgt.mouseOverCount == 0) tgt.onMouseOut();

		tgt.mouseOver = tgt.mouseOverCount > 0;
	}
}