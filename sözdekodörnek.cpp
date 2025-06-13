/*Bu rutin, cagirilan rutin tarafindan saglanan bir hata koduna dayali olarak bir hata mesaji verir.
 Mesajin cikis sekli, kendi bastan alacagi gecerli isleme durumuna baglidir. Basariyi veya basarisizligi gosteren bir deger dondurur. */

Status ReportErrorMessage(ErrorCode errorToReport) {
	// Varsayilan durumu "basarisiz" olarak ayarla
	Status errorMessageStatus = Status_Failure;
	// Hata koduna gore mesaji ara
	Message errorMessage = LookupErrorMessage(errorToReport);
	
	// Eger hata kodu gecerliyse
	if(errorMessage.ValidCode()){
		// İglem medotuna karar ver
		ProcessingMethod errorProcessingMothod = CurrentProcessingMethod();
		
		 // Eger etkilesimli islem yapiyorsan, hata mesajini etkilesimli olarak goruntule ve basariyi bildir
		 if(errorProcessingMethod == ProcessinMethod_Interactive)
		 {
			 DisplayInteractiveMessage(errorMessage.Text());
			 errorMessageStatus = Status_Success;
		 }
		 
		 // Eger komut satiri islemi yapiyorsan, hata mesajini komut 
		 // satirina kaydet ve basariyi bildir
		else if(errorProcessingMethod == ProcessingMethod_CommandLine){
			CommandLine messageLog;
			if(messageLog.Status == CommandLineStatus.OK) {
				messageLog.AddMessageToMessageQueue(errorMessage.Text());
				messageLog.FlushMessageQueue();
				errorMessageStatus = Status_Success;
			}else{
				// hicbir sey yapilmaz cunku rutin zaten hata isliyor
			}			
		}
		else{
		// }hicbir sey yapilmaz cunku rutin zaten hata isliyor
		}
	}
	// Eger hata kodu gecerli degilse, kullaniciya dahili bir hatanin algilandigini bildir
	else{
		DisplayInteractiveMessage("Dahili hata: ReportErrorMessage() gecersiz hata kodu");
	}
		
	// Durum bilgilerini dondur
	return errorMessageStatus;
}
