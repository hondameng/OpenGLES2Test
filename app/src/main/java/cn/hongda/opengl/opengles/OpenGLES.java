package cn.hongda.opengl.opengles;

public class OpenGLES {

	static {
		System.loadLibrary("OpenGLES");
	}

	public static native long init();
	public static native void release(long handle);
	public static native int changeLayout(long handle,int vWidth, int vHeight);

	public static native long createVideoView(long handle,int positionX,int positionY,int realWidth, int realHeight,int drawWidth,int drawHeight);
	public static native int drawVideoFrame(long handle,byte[] data);

	public static native byte[] getFrame();
	public static native int getDrawWidth();
	public static native int getDrawHeigth();

	public static native byte[] getScreenFrame(long handle);
	public static native int getScreenWidth();
	public static native int getScreenHeigth();

	public static native long createPicView(long handle,int positionX,int positionY,int realWidth, int realHeight,int drawWidth,int drawHeight);
	public static native int drawFramePic(long handle,byte[] data);

	/**
	 * 清空图像
	 */
	public static native int clearView();

}
