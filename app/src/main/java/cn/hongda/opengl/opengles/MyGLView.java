package cn.hongda.opengl.opengles;


import java.util.List;


/**
 * 一个能绘制固定位置和滚动位置子view的东西
 */
public class MyGLView {

    //引擎句柄
    private long mHandle;

    /**
     * 初始化GL环境
     */
    public void initGL() {
        mHandle = init();
    }

    /**
     * 当GL view改变时
     * @param width surfaceview 宽
     * @param height surfaceview 高
     */
    public void onChangeGL(int width, int height) {
        changeLayout(mHandle,width, height);
    }

    /**
     * 创建固定位置view  左上角为（0，0）
     * @param positionX 开始位置X坐标
     * @param positionY 开始位置Y坐标
     * @param realWidth 原数据宽度
     * @param realHeight 原数据高度
     * @param drawWidth 绘制宽度
     * @param drawHeight 绘制高度
     * @return
     */
    public long addStaticView(int positionX, int positionY, int realWidth, int realHeight, int drawWidth, int drawHeight){
        long sHandle = createStaticView(mHandle,positionX,positionY,realWidth,realHeight,drawWidth,drawHeight);
        return sHandle;
    }

    /**
     * 创建自由随机滚动view  左上角为（0，0）
     * @param positionX 开始位置X坐标
     * @param positionY 开始位置Y坐标
     * @param realWidth 原数据宽度
     * @param realHeight 原数据高度
     * @param drawWidth 绘制宽度
     * @param drawHeight 绘制高度
     * @return
     */
    public long addScrollView(int positionX, int positionY, int realWidth, int realHeight, int drawWidth, int drawHeight){
        long sHandle = createScrollView(mHandle,positionX,positionY,realWidth,realHeight,drawWidth,drawHeight);
        return sHandle;
    }

    /**
     * 绘制所有子view
     * @param sHandles 子view句柄列表
     * @param rgbDatas 相对于子view将要绘制的数据
     * @return
     */
    public byte[] drawFrame(List<Long> sHandles,List<byte[]> rgbDatas ) {
        if (rgbDatas != null && sHandles != null && rgbDatas.size() == sHandles.size()) {
            clearView(mHandle);
            for (int i = 0 ; i < sHandles.size() ; i ++){
                drawSubFrame(mHandle,sHandles.get(i),rgbDatas.get(i));
            }
            drawFBO(mHandle);
            byte[] rgbByte = getScreenFrame(mHandle);
            return rgbByte;
        }
        return null;

    }


    /**
     * 释放全部GL
     */
    public void relase(){
        release(mHandle);
    }






    static {
        System.loadLibrary("OpenGLES");
    }

    private static native long init();

    private static native void release(long mHandle);

    private static native int changeLayout(long mHandle, int vWidth, int vHeight);

    private static native long createStaticView(long mHandle, int positionX, int positionY, int realWidth, int realHeight, int drawWidth, int drawHeight);

    private static native byte[] getFrame();

    private static native byte[] getScreenFrame(long mHandle);

    private static native long createScrollView(long mHandle, int positionX, int positionY, int realWidth, int realHeight, int drawWidth, int drawHeight);

    /**
     * 绘制子view
     */
    private static native int drawSubFrame(long mHandle,long sHandle, byte[] data);

    public static native int drawFBO(long mHandle);

    /**
     * 清空图像
     */
    private static native int clearView(long mHandle);
}
