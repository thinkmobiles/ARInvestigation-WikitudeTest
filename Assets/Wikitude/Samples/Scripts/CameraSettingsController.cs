using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using Wikitude;

public class CameraSettingsController : SampleController 
{
	public WikitudeCamera Camera;
	public GameObject ControlsLayout;
	public Dropdown PositionDropdown;
	public Dropdown FocusModeDropdown;
	public GameObject AutoFocusRestrictionLayout;
	public Dropdown AutoFocusRestrictionDropdown;
	public Dropdown FlashModeDropdown;
	public GameObject ZoomLayout;
	public Scrollbar ZoomScrollbar;

	void Start() {
		PositionDropdown.value = (int)Camera.DevicePosition;
		FocusModeDropdown.value = (int)Camera.FocusMode;
		if (Application.platform == RuntimePlatform.IPhonePlayer) {
			AutoFocusRestrictionDropdown.value = (int)Camera.AutoFocusRestriction;
		} else {
			AutoFocusRestrictionLayout.SetActive(false);
		}
		FlashModeDropdown.value = (int)Camera.FlashMode;
		if (Mathf.Approximately(Camera.MaxZoomLevel, 1.0f)) {
			ZoomLayout.SetActive(false);
		} else {
			ZoomScrollbar.value = (Camera.ZoomLevel - 1.0f) / (Camera.MaxZoomLevel - 1.0f);
		}
	}

	public void OnCameraControlsButtonClicked() {
		ControlsLayout.SetActive(!ControlsLayout.activeSelf);
	}

	public void OnPositionChanged(int newPosition) {
		Camera.DevicePosition = (CaptureDevicePosition)newPosition;
	}

	public void OnFocusModeChanged(int newFocusMode) {
		Camera.FocusMode = (CaptureFocusMode)newFocusMode;
	}

	public void OnAutoFocusChanged(int newAutoFocus) {
		Camera.AutoFocusRestriction = (CaptureAutoFocusRestriction)newAutoFocus;
	}

	public void OnFlashModeChanged(int newFlashMode) {
		Camera.FlashMode = (CaptureFlashMode)newFlashMode;
	}

	public void OnZoomLevelChanged(float newZoomLevel) {
		Camera.ZoomLevel = newZoomLevel * (Camera.MaxZoomLevel - 1.0f) + 1.0f;
	}
}
