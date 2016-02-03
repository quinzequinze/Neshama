//
//  BACtrack
//  Copyright (c) KHN Solutions LLC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MainScreen.h"
#import "BACtrack.h"
#import <AudioToolbox/AudioToolbox.h>




@interface MainScreen () <BacTrackAPIDelegate>
{
    BacTrackAPI * mBacTrack;
    NSMutableArray * breathalyzers;
    UIImageView *imageView;
    //
    NSMutableArray *imageNames;
    NSMutableArray *images;
    UIImageView *animationImageView;
    BOOL button;
}
@end

@implementation MainScreen
@synthesize delegate;

- (void)viewDidLoad
{
    [super viewDidLoad];
    //pas de veille
    [UIApplication sharedApplication].idleTimerDisabled = YES;
    
    //sdk BACtrack
    mBacTrack = [[BacTrackAPI alloc] initWithDelegate:delegate];
    mBacTrack.delegate = self;
    breathalyzers = [NSMutableArray array];
    [mBacTrack connectToNearestBreathalyzer];
    
    //server
    asyncSocket = [[GCDAsyncSocket alloc] initWithDelegate:self delegateQueue:dispatch_get_main_queue()];
    connectedSockets = [[NSMutableArray alloc] init];
    if (!asyncSocket) {
        NSLog(@"ソケットの作成に失敗");
    } else {
        NSLog(@"ソケットの作成に成功");
        NSError *error = nil;
        uint16_t port = 20000;
        if(![asyncSocket acceptOnPort:port error:&error]){
            NSLog(@"Connection refusée");
        }else{
            NSLog(@"Attente de connexion");
        }
    }
    
    
    //bouton
    UIButton *but= [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [but addTarget:self action:@selector(buttonClicked:) forControlEvents:UIControlEventTouchUpInside];
    [but setFrame:CGRectMake(0,0, 320, 600)];
    [but setExclusiveTouch:YES];
    //but.backgroundColor = [UIColor greenColor];
    [self.view addSubview:but];
    
    //Sequence d'image Init
    animationImageView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 340, 568)];
    button=YES;


    
}

-(void)viewDidAppear:(BOOL)animated
{
    [mBacTrack startScan];
    [mBacTrack stopScan];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}


-(void) buttonClicked:(UIButton*)sender
{
    if(button){
        NSLog(@"Button Tapped");
        [mBacTrack startCountdown];
        NSData *data = [START dataUsingEncoding:NSUTF8StringEncoding];
        [activeSocket writeData:data withTimeout:5 tag:0];
        button=NO;
    }
}


-(void)BacTrackError:(NSError*)error
{
    if(error)
    {
        NSLog(@"CHECKCHECK %@", error.description);
        if(activeSocket){
            NSData *data = [ERROR dataUsingEncoding:NSUTF8StringEncoding];
            [activeSocket writeData:data withTimeout:5 tag:0];
        }
    }

}

-(void)BacTrackCountdown:(NSNumber *)number executionFailure:(BOOL)failure
{
    if (failure)
    {
        [self BacTrackError:nil];
        return;
    }
    else

    NSLog(@"countdown : %@", [NSString stringWithFormat: @"%d", number.intValue]);
    
    imageNames =[[NSMutableArray alloc] init];
    images = [[NSMutableArray alloc] init];
    int l = 1;
    for (int i = 1; i <= l; i++) {
        [imageNames addObject:[NSString stringWithFormat:@"%d.jpg", number.intValue]];
    }
    for (int i = 0; i < imageNames.count; i++) {
        [images addObject:[UIImage imageNamed:[imageNames objectAtIndex:i]]];
    }
    animationImageView.animationImages = images;
    animationImageView.animationDuration = 0.5;
    [self.view addSubview:animationImageView];
    [animationImageView startAnimating];
    if(activeSocket){
    NSData *data = [[NSString stringWithFormat: @"warming %d", number.intValue]dataUsingEncoding:NSUTF8StringEncoding];
        [activeSocket writeData:data withTimeout:5 tag:0];
    }
}


- (void)BacTrackStart
{
    imageNames =[[NSMutableArray alloc] init];
    images = [[NSMutableArray alloc] init];
    int l = 23;
    for (int i = 1; i <= l; i++) {
        [imageNames addObject:[NSString stringWithFormat:@"soufflez%d.jpg", i]];
    }
    for (int i = 0; i < imageNames.count; i++) {
        [images addObject:[UIImage imageNamed:[imageNames objectAtIndex:i]]];
    }
    animationImageView.animationImages = images;
    [self.view addSubview:animationImageView];
    [animationImageView startAnimating];
    
    
    if(activeSocket){
        NSData *data = [BLOW dataUsingEncoding:NSUTF8StringEncoding];
        [activeSocket writeData:data withTimeout:5 tag:0];
    }
}

- (void)BacTrackBlow
{
    imageNames =[[NSMutableArray alloc] init];
    images = [[NSMutableArray alloc] init];
    int l = 107;
    for (int i = 1; i <= l; i++) {
        [imageNames addObject:[NSString stringWithFormat:@"continuez%d.jpg", i]];
    }
    for (int i = 0; i < imageNames.count; i++) {
        [images addObject:[UIImage imageNamed:[imageNames objectAtIndex:i]]];
    }
    animationImageView.animationImages = images;
    animationImageView.animationDuration = 4;
    [self.view addSubview:animationImageView];
    [animationImageView startAnimating];

    
    if(activeSocket){
        NSData *data = [KEEP_BLOWING dataUsingEncoding:NSUTF8StringEncoding];
        [activeSocket writeData:data withTimeout:5 tag:0];
    }
}

- (void)BacTrackAnalyzing
{
    imageNames =[[NSMutableArray alloc] init];
    images = [[NSMutableArray alloc] init];
    int l = 107;
    for (int i = 1; i <= l; i++) {
        [imageNames addObject:[NSString stringWithFormat:@"analyse%d.jpg", i]];
    }
    for (int i = 0; i < imageNames.count; i++) {
        [images addObject:[UIImage imageNamed:[imageNames objectAtIndex:i]]];
    }
    animationImageView.animationImages = images;
        animationImageView.animationDuration = 4;
    [self.view addSubview:animationImageView];
    [animationImageView startAnimating];
    
    if(activeSocket){
        NSData *data = [ANALYSING dataUsingEncoding:NSUTF8StringEncoding];
        [activeSocket writeData:data withTimeout:5 tag:0];
    }
}


-(void)BacTrackResults:(CGFloat)bac
{
    imageNames =[[NSMutableArray alloc] init];
    images = [[NSMutableArray alloc] init];
    int l = 147;
    for (int i = 1; i <= l; i++) {
        [imageNames addObject:[NSString stringWithFormat:@"commencez%d.jpg", i]];
    }
    for (int i = 0; i < imageNames.count; i++) {
        [images addObject:[UIImage imageNamed:[imageNames objectAtIndex:i]]];
    }
    animationImageView.animationImages = images;
    animationImageView.animationDuration = 6;
    [self.view addSubview:animationImageView];
    
    [animationImageView startAnimating];
    
    button=YES;
    if(activeSocket){
        NSData *data = [[NSString stringWithFormat: @"reading %.2f", bac]dataUsingEncoding:NSUTF8StringEncoding];
        [activeSocket writeData:data withTimeout:5 tag:0];
    }
}

-(void)BacTrackConnected:(BACtrackDeviceType)device
{
    NSLog(@"Connected to BACtrack device");
    if(activeSocket){
        NSData *data = [CONNECTED dataUsingEncoding:NSUTF8StringEncoding];
        [activeSocket writeData:data withTimeout:5 tag:0];
    }
    //[self animateBackgroundColor:[UIColor greenColor]];
    imageNames =[[NSMutableArray alloc] init];
    images = [[NSMutableArray alloc] init];
    
    int l = 147;
    for (int i = 1; i <= l; i++) {
        [imageNames addObject:[NSString stringWithFormat:@"commencez%d.jpg", i]];
    }
    for (int i = 0; i < imageNames.count; i++) {
        [images addObject:[UIImage imageNamed:[imageNames objectAtIndex:i]]];
    }
    animationImageView.animationImages = images;
    animationImageView.animationDuration = 6;
    [self.view addSubview:animationImageView];
    
    [animationImageView startAnimating];
     
        button=YES;
}

-(void)BacTrackDisconnected
{

    imageNames =[[NSMutableArray alloc] init];
    images = [[NSMutableArray alloc] init];
    int l = 1;
    for (int i = 1; i <= l; i++) {
        [imageNames addObject:[NSString stringWithFormat:@"error%d.jpg", i]];
    }
    for (int i = 0; i < imageNames.count; i++) {
        [images addObject:[UIImage imageNamed:[imageNames objectAtIndex:i]]];
    }
    animationImageView.animationImages = images;
    animationImageView.animationDuration = 6;
    [self.view addSubview:animationImageView];
    
    [animationImageView startAnimating];

    button=NO;
    //[mBacTrack disconnect];
    if(activeSocket){
        NSData *data = [DISCONNECTED dataUsingEncoding:NSUTF8StringEncoding];
        [activeSocket writeData:data withTimeout:5 tag:0];
    }
    NSLog(@"Disonnected from BACtrack device");
    [mBacTrack connectToNearestBreathalyzer];
}

-(void)BacTrackConnectTimeout
{
    [mBacTrack connectToNearestBreathalyzer];
}

-(NSTimeInterval)BacTrackGetTimeout
{
    return 10;
}

-(void)BacTrackFoundBreathalyzer:(Breathalyzer*)breathalyzer
{
    NSString *breathalyzerUUID = [breathalyzer.peripheral.identifier UUIDString];
    for (Breathalyzer * breath in breathalyzers)
    {
        NSString *breathUUID = [breath.peripheral.identifier UUIDString];
        if ([breathUUID isEqualToString:breathalyzerUUID])
        {
            NSLog(@"%@: Duplicate Breathalyzer UUID found!",self.class.description);
            return;
        }
    }
    [breathalyzers addObject:breathalyzer];
}

- (void) BacTrackBatteryVoltage:(NSNumber *)number
{
    //NSLog(@"Battery Voltage: %f", [number floatValue]);
}

-(void)BacTrackFirmwareVersion:(NSString*)version
{
    //NSLog(@"%@", version);
}


//SERVER EVENTS//////////////////////////////////////////////////////////////////////////////////////////////////
#pragma mark - GCDAsyncSocketDelegate
- (void)socket:(GCDAsyncSocket *)sock didAcceptNewSocket:(GCDAsyncSocket *)newSocket{
    NSLog(@"Accepted new Socket from %@:%hu",[newSocket connectedHost],[newSocket connectedPort]);
    [connectedSockets addObject:newSocket];
    [newSocket setAutoDisconnectOnClosedReadStream:YES];
    [newSocket readDataToData:[GCDAsyncSocket CRLFData] withTimeout:-1 tag:0];
    
    activeSocket= newSocket;
    
    NSData *data = [@"Welcome this is vigophone" dataUsingEncoding:NSUTF8StringEncoding];
    [activeSocket writeData:data withTimeout:5 tag:0];


}

- (void)socket:(GCDAsyncSocket *)sock didReadData:(NSData *)data withTag:(long)tag{
    AudioServicesPlaySystemSound(1000);
    NSString *msg = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    msg = [msg substringToIndex:[msg length] - 2];
    NSLog(@"New message from client: %@",msg);
    [sock readDataToData:[GCDAsyncSocket CRLFData] withTimeout:-1 tag:0];
    
}

-(void)socketDidDisconnect:(GCDAsyncSocket *)sock withError:(NSError *)err{
    NSLog(@"Disconect:%@:%hu",[sock connectedHost],[sock connectedPort]);
    // asyncSocket = nil;
    // asyncSocket.delegate = nil;
}

-(void)dealloc
{
    [asyncSocket setDelegate:nil];
    [asyncSocket disconnect];
}

- (void) animateBackgroundColor:(UIColor*)color {
    [UIView animateWithDuration:1.0f animations:^{
        self.view.backgroundColor =  color;
    } completion:^(BOOL finished) {
    }];
    
}

-(void)viewDidUnload
{
    [super viewDidUnload];
    NSLog(@"viewDidUnload");

}

@end