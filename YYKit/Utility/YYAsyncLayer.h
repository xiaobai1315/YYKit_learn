//
//  YYAsyncLayer.h
//  YYKit <https://github.com/ibireme/YYKit>
//
//  Created by ibireme on 15/4/11.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@class YYAsyncLayerDisplayTask;

NS_ASSUME_NONNULL_BEGIN

/**
 The YYAsyncLayer class is a subclass of CALayer used for render contents asynchronously.
 @discussion When the layer need update it's contents, it will ask the delegate
 for a async display task to render the contents in a background queue.
 
 YYAsyncLayer是CALayer的子类，用来异步渲染内容；
 当layer需要更新他的内容，他会在后台队列请求代理一个异步的渲染内容的任务；
 */
@interface YYAsyncLayer : CALayer
/// Whether the render code is executed in background. Default is YES.
// 渲染任务是否在后台执行
@property BOOL displaysAsynchronously;
@end


/**
 The YYAsyncLayer's delegate protocol. The delegate of the YYAsyncLayer (typically a UIView)
 must implements the method in this protocol.
 
 YYAsyncLayer代理协议。YYAsyncLayer的代理(通常是一个view)必须实现协议的方法。
 */
@protocol YYAsyncLayerDelegate <NSObject>
@required
/// This method is called to return a new display task when the layer's contents need update.
// 当layer的内容需要更新时，调用这个方法返回一个新的显示任务；
- (YYAsyncLayerDisplayTask *)newAsyncDisplayTask;
@end


/**
 A display task used by YYAsyncLayer to render the contents in background queue.
 YYAsyncLayer用来在后台队列渲染内容的任务；
 */
@interface YYAsyncLayerDisplayTask : NSObject

/**
 This block will be called before the asynchronous drawing begins.
 It will be called on the main thread.
 
 block param layer:  The layer.
 
 这个block会在异步渲染开始之前调用；必须在主队列调用；
 */
@property (nullable, nonatomic, copy) void (^willDisplay)(CALayer *layer);

/**
 This block is called to draw the layer's contents.
 
 @discussion This block may be called on main thread or background thread,
 so is should be thread-safe.
 
 block param context:      A new bitmap content created by layer.
 block param size:         The content size (typically same as layer's bound size).
 block param isCancelled:  If this block returns `YES`, the method should cancel the
 drawing process and return as quickly as possible.
 
 这个block用来绘制layer的内容。
 这个block在主队列或后台线程都可以调用，因此是线程安全的；
 
 block param context:layer创建的新的位图内容
 block param size: 内容大小，通常和layer的boundsize一样；
 block param isCancelled:如果这个block返回yes，方法会立即取消绘制过程
 */
@property (nullable, nonatomic, copy) void (^display)(CGContextRef context, CGSize size, BOOL(^isCancelled)(void));

/**
 This block will be called after the asynchronous drawing finished.
 It will be called on the main thread.
 
 block param layer:  The layer.
 block param finished:  If the draw process is cancelled, it's `NO`, otherwise it's `YES`;
 
 异步绘制结束时调用这个block，必须在主线程调用
 
 block param layer: layer
 block param finished:如果绘制处理被取消了，返回NO，
 */
@property (nullable, nonatomic, copy) void (^didDisplay)(CALayer *layer, BOOL finished);


@end

NS_ASSUME_NONNULL_END
