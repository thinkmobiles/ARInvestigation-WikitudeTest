using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using Wikitude;

public class Client3DTrackingController : SampleController {
	
	public Text RecordingQualityText;
	public Image RecordingQualityBackground;
	public Button RecordButton;

	public GameObject TrackablePrefab;
	public TrackingMapRecorder Recorder;

	private ClientTracker _tracker;
	private string _mapPath;

	void Awake() {
		Recorder.TrackingMapName = "TrackingMap";
	}

	#region UI Events
	public void OnStartRecording() {
		RecordButton.gameObject.SetActive(false);
		Recorder.StartRecording();
		OnRecordingQualityChanged(RecordingQuality.Bad);
	}
	#endregion

	#region TrackingMapRecorder Events
	public void OnRecordingFinished(string mapPath) {
		RecordingQualityText.text = "Loading map...";
		RecordingQualityBackground.color = Color.white;

		_mapPath = mapPath;
		Load3DTracker();
	}

	public void OnRecordingError(string error) {
		Debug.Log("Recording error: " + error + ". Restarting...");

		Recorder.StopRecording();
		Recorder.StartRecording();
	}

	public void OnRecordingQualityChanged(RecordingQuality newQuality) {
		switch (newQuality) {
		case RecordingQuality.Bad: 
			RecordingQualityText.text = "Bad";
			RecordingQualityBackground.color = Color.red;
			break;
		case RecordingQuality.Average:
			RecordingQualityText.text = "Average";
			RecordingQualityBackground.color = Color.yellow;
			break;
		case RecordingQuality.Good:
			RecordingQualityText.text = "Good";
			RecordingQualityBackground.color = Color.green;

			break;
		default:
			break;
		}

		if (newQuality == RecordingQuality.Good) {
			Recorder.StopRecording();
		}
	}
	#endregion

	#region ClientTracker Events
	public void OnTrackerFinishedLoading(string targetPath) {
		RecordingQualityText.text = "Tracking";
	}

	public new void OnTrackerLoadingError(string error) {
		Debug.Log("Error loading 3D client tracker: " + error + ". Reloading...");

		Load3DTracker();
	}
	#endregion

	private void Load3DTracker() {
		if (_mapPath == null) {
			Debug.Log("No map to load!");
			return;
		}

		if (_tracker != null) {
			Destroy(_tracker.gameObject);
		}

		var trackerObject = new GameObject("ClientTracker");
		_tracker = trackerObject.AddComponent<Wikitude.ClientTracker>();
		_tracker.UseCustomUrl = true;
		_tracker.Use3DTracking = true;
		_tracker.TargetPath = "file://" + _mapPath;
		_tracker.OnTrackerFinishedLoading.AddListener(OnTrackerFinishedLoading);
		_tracker.OnTrackerLoadingError.AddListener(OnTrackerLoadingError);

		var trackableObject = GameObject.Instantiate(TrackablePrefab);
		trackableObject.transform.SetParent(trackerObject.transform, false);
	}
}
