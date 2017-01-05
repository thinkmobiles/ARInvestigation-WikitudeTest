using UnityEngine;
using UnityEngine.UI;
using System;
using System.Collections;
using Wikitude;

public class PluginController : SampleController
{
	public Text ResultText;
	private BarcodePlugin _plugin;

	private bool _initialized = false;

	void Start() {
		if (Application.platform == RuntimePlatform.Android || Application.platform == RuntimePlatform.IPhonePlayer) {
			_plugin = new BarcodePlugin();
		} else {
			Debug.Log("Current platform is not supported");
			Destroy(this);
		}
	}

	public void OnCameraFrameAvailable(Frame frame) {

		if (!_initialized) {
			_plugin.Initialize(frame.Width, frame.Height);
			_initialized = true;
		}

		string barcode = _plugin.GetBarcode(frame);

		if (barcode != null) {
			ResultText.text = barcode;
		} else {
			ResultText.text = "Could not detect any barcodes";
		}
	}

	void OnDestroy() {
		if (_plugin != null) {
			_plugin.Destroy();
		}
	}
}
