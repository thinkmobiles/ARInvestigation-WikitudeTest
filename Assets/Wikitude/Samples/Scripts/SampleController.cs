using UnityEngine;
#if UNITY_5_3_OR_NEWER
using UnityEngine.SceneManagement;
#endif

public class SampleController : MonoBehaviour {
	
	public void OnBackButtonClicked() {
#if UNITY_5_3_OR_NEWER
		SceneManager.LoadScene("Main Menu");
#else
		Application.LoadLevel("Main Menu");
#endif
	}

	public virtual void OnTrackerLoadingError(string error) {
		Debug.LogError("Tracker loading error: " + error);
	}

	protected virtual void Update() {
		// Also handles the back button on Android
		if (Input.GetKeyDown(KeyCode.Escape)) { 
			OnBackButtonClicked();
		}
	}
}
