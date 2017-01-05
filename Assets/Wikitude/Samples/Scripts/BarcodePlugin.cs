using System;
using System.Runtime.InteropServices;

public class BarcodePlugin
{
#if UNITY_ANDROID
	[DllImport("barcode")]
	private static extern void initialize(int width, int height);

	[DllImport("barcode")]
	private static extern string get_barcode(int width, int height, IntPtr buffer);

	[DllImport("barcode")]
	private static extern void destroy();
#else
	[DllImport("__Internal")]
	private static extern void initialize(int width, int height);

	[DllImport("__Internal")]
	private static extern string get_barcode(int width, int height, IntPtr buffer);

	[DllImport("__Internal")]
	private static extern void destroy();
#endif

	public void Initialize(int width, int height) {
		initialize(width, height);
	}

	public string GetBarcode(Wikitude.Frame frame) {
		return get_barcode(frame.Width, frame.Height, frame.Data);
	}

	public void Destroy() {
		destroy();
	}
}

