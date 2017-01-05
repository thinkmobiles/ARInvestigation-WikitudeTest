using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;
using Wikitude;

public class ContinuousTrackerController : SampleController 
{
	public CloudTracker Tracker;
	public Text buttonText;
	private bool _trackerRunning = false;
	private bool _trackerLoaded = false;
	private bool _isContinuousRecognitionRunning = false;
	private bool _targetFoundLocally = false;

	#region UI Events
	public void OnToggleClicked() {
		if (Tracker != null && _trackerLoaded) {
			if (_trackerRunning) {
				buttonText.text = "Press to start scanning";
				StopContinuousCloudRecognition();
			} else {
				buttonText.text = "Scanning";
				StartContinuousCloudRecognition();
			}
			_trackerRunning = !_trackerRunning;
		}
	}
	#endregion

	#region Tracker Events
	public void OnTrackerFinishedLoading() {
		_trackerLoaded = true;
	}

	public new void OnTrackerLoadingError(string errorMessage) {
		
	}

	public void OnRecognitionSuccessful(bool recognized, CloudTargetInfo info) {
		if (recognized) {
			// If the cloud recognized a target, we stop continuous recognition and track that target locally
			Tracker.StopContinuousRecognition();

			// In case we don't actually find the target locally within a time limit, restart the continuous recognition
			// Because there is a delay between when the message from the cloud arrives and when we actually start tracking
			// the target, if the target is actually lost during that delay, OnExitFieldOfVision would never be called.
			_targetFoundLocally = false;
			StartCoroutine(RestartContinuousCloudRecognition());
		}
	}
	#endregion

	public void OnTargetFound() {
		_targetFoundLocally = true;
	}

	public void OnTargetLost() {
		if (_isContinuousRecognitionRunning) {
			// If we lose the recognized target locally, we restart continuous recognition
			Tracker.StartContinuousRecognition(1.5);
		}
	}

	private IEnumerator RestartContinuousCloudRecognition() {
		yield return new WaitForSeconds(5.0f);
		if (!_targetFoundLocally && _isContinuousRecognitionRunning) {
			Tracker.StartContinuousRecognition(1.5);
		}
	}

	private void StartContinuousCloudRecognition() {
		Tracker.StartContinuousRecognition(1.5);
		_isContinuousRecognitionRunning = true;
	}

	private void StopContinuousCloudRecognition() {
		Tracker.StopContinuousRecognition();
		_isContinuousRecognitionRunning = false;
	}
}
