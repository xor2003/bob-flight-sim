//---------------------------------------------------------------------------
#ifndef SelTargH
#define SelTargH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSelectTarget : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TBevel *Bevel1;
	TLabel *Label1;
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y);
private:	// User declarations
	bool move;
public:		// User declarations
	__fastcall TSelectTarget(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TSelectTarget *SelectTarget;
//---------------------------------------------------------------------------
#endif
