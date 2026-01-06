#include "affiliate_bar.h"

AffiliateBar *AffiliateBar::addAffiliateBarChild(ObjectScreen *parent, glm::vec2 size, Anchor anchor)
{
    auto bar = new AffiliateBar();
    bar->init();
    bar->setAnchor(anchor);
    
    bar->setSize(size);
    if (parent){
        bar->setParent(parent);
        parent->addChild(bar);
    }
    return bar;
}

void AffiliateBar::render()
{
    ObjectAffiliate::render();
    auto pos = parent_->getRenderPosition() + offset_;
    if (percentage_ > 0.7f){
        game_.renderHBar(pos, size_, percentage_, color_high_);
    } else if (percentage_ > 0.3f){
        game_.renderHBar(pos, size_, percentage_, color_mid_);
    } else {
        game_.renderHBar(pos, size_, percentage_, color_low_);
    }
}
