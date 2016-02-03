//
//  MainScreen.h
//  BACtrackSDKDemo
//
//  Created by Andrew Greteman on 9/30/14.
//  Copyright (c) KHN Solutions LLC. All rights reserved.


#import <UIKit/UIKit.h>
#import "BACtrack.h"
#import "GCDAsyncSocket.h"

#define CONNECTED @"connected"
#define DISCONNECTED @"deconnected"
#define BLOW @"blow"
#define KEEP_BLOWING @"keepBlowing"
#define WARMING @"warming"
#define ERROR @"error"
#define READING @"reading"
#define ANALYSING @"analysing"
#define START @"start"

@interface MainScreen : UIViewController <GCDAsyncSocketDelegate>
{
    IBOutlet UIImageView *monImage;
    IBOutlet UIButton *mTakeTest;

    GCDAsyncSocket *asyncSocket;
    NSMutableArray *connectedSockets;
    GCDAsyncSocket *activeSocket;
}
@property (nonatomic, retain) id <BacTrackAPIDelegate> delegate;
@property(nonatomic, copy) NSArray <UIImage *> *anim;

@end
