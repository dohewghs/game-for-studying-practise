#pragma once
#include "IEntityPresenter.h"
#include "Entity.h"
#include "ResourceManager.h"

class BaseEntityPresenter : public IEntityPresenter
{
public:
	BaseEntityPresenter(Entity* entity = nullptr) : IEntityPresenter(entity)
	{
		this->addAnimation(ResourceManager::getTexture("hero_idle"), "idle", 10, 2, 0, -40);
		this->addAnimation(ResourceManager::getTexture("Character Run"), "run", 16, 2, 0, -40);
		this->addAnimation(ResourceManager::getTexture("hurt"), "hurt", 4, 2, 0, -40);
	}
	
	~BaseEntityPresenter()
	{
		this->entity = nullptr;
	}

	void present(SDL_Renderer* renderer) override
	{

		const AnimationData& anim = getCurrentAnimation();

		if (!anim.texture)
			return;

		if (this->entity->statistics.hp <= 0)
		{
			setRedColor(anim.texture);
			this->cancelUpdate = true;
		}
		

		SDL_FRect srcRect =
		{
			anim.state.current_frame * anim.frame_width, 0.0f,
			anim.frame_width, anim.frame_height
		};

		//SDL_FRect dstRect = toSDLFRect(entity->hitBox);

		SDL_FRect entityrect = toSDLFRect(entity->getHitBox());

		SDL_FRect dstRect;
		dstRect.x = entityrect.x;
		dstRect.y = entityrect.y;
		dstRect.w = anim.frame_width;
		dstRect.h = anim.frame_height;

		Vector2 center = CenterOf(entityrect);
		
		ApplyScale(dstRect, anim.scale);

		Centralize(dstRect, center);

		ApplyOffset(dstRect, { anim.offset_x, anim.offset_y });

		RenderCurrentTexture(renderer, &srcRect, &dstRect);

		restoreColor(anim.texture);
	}	

private:
	void ApplyScale(SDL_FRect& rect, double scaleFactor)
	{
		rect.w *= scaleFactor;
		rect.h *= scaleFactor;
	}
	void ApplyOffset(SDL_FRect& rect, Vector2 offset)
	{
		rect.x += offset.x;
		rect.y += offset.y;
	}

	Vector2 CenterOf(const SDL_FRect& rect)
	{
		return {
			rect.x + (rect.w / 2.0f),
			rect.y + (rect.h / 2.0f)
		};
	}

	void Centralize(SDL_FRect& rect, Vector2 center)
	{
		rect.x = center.x - (rect.w / 2.0f);
		rect.y = center.y - (rect.h / 2.0f);
	}

	void setRedColor(SDL_Texture* texture)
	{
		SDL_SetTextureColorMod(texture, 255, 0, 0);
		SDL_SetTextureAlphaMod(texture, 128);
	}

	void restoreColor(SDL_Texture* texture)
	{
		SDL_SetTextureColorMod(texture, 255, 255, 255);
		SDL_SetTextureAlphaMod(texture, 255);
	}
};