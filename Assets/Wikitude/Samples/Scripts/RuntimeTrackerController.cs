using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using Wikitude;

public class RuntimeTrackerController : SampleController
{
	public InputField Url;
	public GameObject TrackablePrefab;
	public GameObject CarInstructions;

	private ClientTracker _currentTracker;
	private bool _isLoadingTracker = false;

	public void OnLoadTracker() {
		if (_isLoadingTracker) {
			// Wait until previous request was completed.
			return;
		}
		if (_currentTracker != null) {
			Destroy(_currentTracker.gameObject);
		}

		_isLoadingTracker = true;

		GameObject trackerObject = new GameObject("ClientTracker");
		_currentTracker = trackerObject.AddComponent<ClientTracker>();
		_currentTracker.UseCustomUrl = true;
		_currentTracker.TargetPath = Url.text;

		_currentTracker.OnTrackerFinishedLoading.AddListener(OnTrackerFinishedLoading);
		_currentTracker.OnTrackerLoadingError.AddListener(OnTrackerLoadingError);

		GameObject trackableObject = GameObject.Instantiate(TrackablePrefab);
		trackableObject.transform.SetParent(_currentTracker.transform, false);
	}

	public void OnTrackerFinishedLoading(string path) {
		CarInstructions.SetActive(true);

		_isLoadingTracker = false;
	}

	public override void OnTrackerLoadingError(string error) {
		base.OnTrackerLoadingError(error);
		_isLoadingTracker = false;
	}
}
