using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using Wikitude;

public class OnClickTrackerController : SampleController
{
	public CloudTracker Tracker;
	public Text InfoText;
	public Button RecognizeButton;
	public Text ButtonText;

	public void OnRecognizeClicked() {
		RecognizeButton.enabled = false;
		ButtonText.text = "Recognizing...";

		Tracker.Recognize();
	}

	public new void OnTrackerLoadingError(string error) {
		InfoText.text = "Error loading tracker!";
	}

	public void OnTrackerFinishedLoading() {
		RecognizeButton.enabled = true;
		ButtonText.text = "Recognize";
	}

	public void OnRecognitionSuccessful(bool targetRecognized, CloudTargetInfo target) {
		RecognizeButton.enabled = true;
		ButtonText.text = "Recognize";
		if (targetRecognized) {
			InfoText.text = target.Info["name"];
		} else {
			InfoText.text = "No target recognized";
		}
	}

	public void OnRecognitionFailed(int errorCode, string message) {
		RecognizeButton.enabled = false;
		ButtonText.text = "Recognize";
		InfoText.text = "Recognition failed!";
	}
}
