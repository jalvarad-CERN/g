# g
Data review: clusterization of pp 13 TeV data

/-----------------------------------------------------------------
This analysis makes a very basic study on the characteristics of the runs
by comparing a global average in the transverse moment distributions with
respect to those corresponding to the specific runs of the period.
/-----------------------------------------------------------------
After running the run analysis in "terminate" mode with SetMergeViaJDL (kTRUE);
download the .root files corresponding to each run,
I use the command

  alien.py cp -T n -select AnalysisResults.root /alice/cern.ch/user/myuserfolder file: //./

where n is the number of runs of the period.
Then obtain the average of the period with
SetMergeViaJDL (kFALSE);
/-----------------------------------------------------------------
Finally, run the PostA.C

