#include "StPicoRpsCollection.h"
#include "StMuDSTMaker/COMMON/StMuRpsCollection.h"
#include <algorithm>


ClassImp(StPicoRpsCollection)

StPicoRpsCollection::StPicoRpsCollection(StMuRpsCollection & rps){

    mSiliconBunch = rps.siliconBunch();

	for(int i=0;i<mNumberOfRomanPot;i++){

		mNumberPlanesWithClusters[i]  = rps.numberOfPlanesWithClusters(i);
		mStatusRomanPot[i]   = rps.status(i);
		mADC[i][0] = rps.adc(i,0);
		mADC[i][1] = rps.adc(i,1);
		mTAC[i][0] = rps.tac(i,0);
		mTAC[i][1] = rps.tac(i,1);
	 												
		for(int j=0;j<mNumberOfPlanes;j++){

			mOffsetPlane[i][j]  = rps.offsetPlane(i,j);
			mzPlane[i][j]  = rps.zPlane(i,j);
			mAnglePlane[i][j]  = rps.anglePlane(i,j);
			mOrientationPlane[i][j]  = rps.orientationPlane(i,j);		
			mStatusPlane[i][j]  = rps.statusPlane(i,j);	
			mNumberOfClusters[i][j]  = rps.numberOfClusters(i,j);
			
			for(int k=0;k<mNumberOfClusters[i][j];k++){
			
				mPositionCluster[i][j].push_back(rps.positionCluster(i,j,k));
				mPositionRMSCluster[i][j].push_back(rps.positionRMSCluster(i,j,k));
				mLengthCluster[i][j].push_back(rps.lengthCluster(i,j,k));
				mEnergyCluster[i][j].push_back(rps.energyCluster(i,j,k));				
				mXYCluster[i][j].push_back(rps.xyCluster(i,j,k));				
				mQualityCluster[i][j].push_back(rps.qualityCluster(i,j,k));		

			}
		}
	}

	// Add all of the track points
	int nTrackPoints = rps.numberOfTrackPoints();
	for ( int i = 0; i < nTrackPoints; i++ ){
		addTrackPoint( rps.trackPoint(i) );
	}

	// Need to mirror over the StMuRpsTracks
	int nTracks = rps.numberOfTracks();
	for ( int iTrack = 0; iTrack < nTracks; iTrack++ ){
		StPicoRpsTrack * picoRpsTrack = new StPicoRpsTrack();

		// Add the track points to the Tracks, if they are already in the collection (and they should be)
		// then they wont be added again
		for ( int iStation = 0; iStation < StPicoRpsTrack::mNumberOfStationsInBranch; iStation++ ){
			if ( rps.track(iTrack) && rps.track(iTrack)->trackPoint( iStation ) ){
				StPicoRpsTrackPoint * ptp = addTrackPoint( rps.track(iTrack)->trackPoint( iStation ) );
				picoRpsTrack->setTrackPoint( ptp, iStation );
			}
		}
		// Set the Track's attributes
		picoRpsTrack->setP( TVector3( rps.track(iTrack)->pVec().x(), rps.track(iTrack)->pVec().y(), rps.track(iTrack)->pVec().z() ) );
		picoRpsTrack->setBranch( rps.track(iTrack)->branch() );
		picoRpsTrack->setType( (StPicoRpsTrack::StPicoRpsTrackType)rps.track(iTrack)->type() );

		// add it to collection
		mTracks.push_back( picoRpsTrack );
	}
}



StPicoRpsTrackPoint* StPicoRpsCollection::addTrackPoint(const StMuRpsTrackPoint* rpsTP ){

	if ( mTrackPointsMap.count( rpsTP ) ){
		return mTrackPointsMap[ rpsTP ]; 
	}

	StPicoRpsTrackPoint * muRpsTrackPoint = new StPicoRpsTrackPoint();

	muRpsTrackPoint->setPosition( TVector3( rpsTP->x(), rpsTP->y(), rpsTP->z() ) );
	muRpsTrackPoint->setQuality( (StPicoRpsTrackPoint::StPicoRpsTrackPointQuality)rpsTP->quality() );
	muRpsTrackPoint->setRpId( rpsTP->rpId() );

	for ( int iPlane = 0; iPlane < StPicoRpsTrackPoint::mNumberOfPlanesInRp; iPlane++ ){
		muRpsTrackPoint->setClusterId( rpsTP->clusterId( iPlane ), iPlane );
	}

	for ( int iPmt = 0; iPmt < StPicoRpsTrackPoint::mNumberOfPmtsInRp; iPmt++ ){
		muRpsTrackPoint->setTime( rpsTP->time( iPmt ), iPmt );
	}

	mTrackPoints.push_back( muRpsTrackPoint );
	mTrackPointsMap[ rpsTP ] = muRpsTrackPoint;
	return muRpsTrackPoint;
}
