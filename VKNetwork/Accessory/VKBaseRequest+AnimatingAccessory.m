//
// Created by Chenyu Lan on 10/30/14.
// Copyright (c) 2014 Fenbi. All rights reserved.
//

#import "VKBaseRequest+AnimatingAccessory.h"
#import "VKAnimatingRequestAccessory.h"


@implementation VKBaseRequest (AnimatingAccessory)

- (VKAnimatingRequestAccessory *)animatingRequestAccessory {
    for (id accessory in self.requestAccessories) {
        if ([accessory isKindOfClass:[VKAnimatingRequestAccessory class]]){
            return accessory;
        }
    }
    return nil;
}

- (UIView *)animatingView {
    return self.animatingRequestAccessory.animatingView;
}

- (void)setAnimatingView:(UIView *)animatingView {
    if (!self.animatingRequestAccessory) {
        [self addAccessory:[VKAnimatingRequestAccessory accessoryWithAnimatingView:animatingView animatingText:nil]];
    } else {
        self.animatingRequestAccessory.animatingView = animatingView;
    }
}

- (NSString *)animatingText {
    return self.animatingRequestAccessory.animatingText;
}

- (void)setAnimatingText:(NSString *)animatingText {
    if (!self.animatingRequestAccessory) {
        [self addAccessory:[VKAnimatingRequestAccessory accessoryWithAnimatingView:nil animatingText:animatingText]];
    } else {
        self.animatingRequestAccessory.animatingText = animatingText;
    }
}

@end
