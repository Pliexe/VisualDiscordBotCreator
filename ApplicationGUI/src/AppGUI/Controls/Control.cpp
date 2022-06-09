/* Copyright (c) 2022 Szabadi László Zsolt
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VisualDiscordBotCreator/blob/master/LICENSE
 */
#include "Control.h"

namespace AppGUI {
	void BaseControl::calculateParentResize()
	{

		if (transform.hasParent()) {
			Transform& parent = transform.parent();
			Vector2D& position = parent.position();
			Size2D& size = parent.size();

			if (m_scale & Scale::Horizontal) size.setWidth(baseWidth * size.width());
			if (m_scale & Scale::Vertical) size.setHeight(baseHeight * size.height());

			int half_width = (size.width() / 2);
			int half_height = (size.height() / 2);
			int temp_x = position.x() + half_width;
			int temp_y = position.y() + half_height;

			if (m_anchor != 0) {
				if (m_anchor & Top) temp_y -= half_height;
				if (m_anchor & Bottom) temp_y += half_height;
				if (m_anchor & Left) temp_x -= half_width;
				if (m_anchor & Right) temp_x += half_width;
			}

			transform.setPosition(temp_x, temp_y);
		}
	}
	void BaseControl::calculateTransform()
	{
		int temp_x, temp_y, temp_height, temp_width, half_height, half_width;

		if (transform.hasParent()) {
			Transform& parent = transform.parent();

			temp_height = parent.position().y() + (m_scale & Height ? (parent.size().height() * baseHeight) : baseHeight);
			temp_width = parent.position().x() + (m_scale & Width ? (parent.size().width() * baseWidth) : baseWidth);

			half_height = temp_height / 2;
			half_width = temp_width / 2;

			temp_x = m_scale & Horizontal ? baseX : parent.size().width() * baseX;
			temp_y = m_scale & Vertical ? baseY : parent.size().height() * baseY;

			transform.setSize(temp_width, temp_height);
		}
		else {
			half_height = (baseHeight / 2);
			half_width = (baseWidth / 2);
			temp_x = baseX - half_width;
			temp_y = baseY - half_height;

			transform.setSize(baseWidth, baseHeight);
		}

		if (m_anchor != 0) {
			if (m_anchor & Top) temp_y -= half_height;
			if (m_anchor & Bottom) temp_y += half_height;
			if (m_anchor & Left) temp_x -= half_width;
			if (m_anchor & Right) temp_x += half_width;
		}

		transform.setPosition(temp_x, temp_y);
	}
	void BaseControl::_onParentResize()
	{
		calculateParentResize();
		onParentResize();
	}
}