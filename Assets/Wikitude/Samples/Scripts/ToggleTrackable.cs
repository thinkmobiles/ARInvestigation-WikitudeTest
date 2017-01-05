using UnityEngine;
using System.Collections;
using Wikitude;

public class ToggleTrackable : MonoBehaviour
{
	private void Awake() {
		gameObject.SetActive(false);
	}

	public virtual void OnEnterFieldOfVision(string targetName) {
		// The target image is now visible in the camera frame. Enable any object or trigger any other events.
		gameObject.SetActive(true);
	}

	public virtual void OnExitFieldOfVision(string targetName) {
		// The target image is now visible in the camera frame. Disable any object or trigger any other events.
		gameObject.SetActive(false);
	}
}
