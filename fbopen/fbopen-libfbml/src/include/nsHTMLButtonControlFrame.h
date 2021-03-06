/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either of the GNU General Public License Version 2 or later (the "GPL"),
 * or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef nsHTMLButtonControlFrame_h___
#define nsHTMLButtonControlFrame_h___

#include "nsCOMPtr.h"
#include "nsHTMLContainerFrame.h"
#include "nsFormControlHelper.h"
#include "nsIFormControlFrame.h"
#include "nsHTMLParts.h"

#include "nsPresContext.h"
#include "nsIPresShell.h"
#include "nsStyleContext.h"
#include "nsLeafFrame.h"
#include "nsCSSRendering.h"
#include "nsISupports.h"
#include "nsStyleConsts.h"
#include "nsIComponentManager.h"
#include "nsButtonFrameRenderer.h"

class nsIRenderingContext;

class nsHTMLButtonControlFrame : public nsHTMLContainerFrame,
                                 public nsIFormControlFrame 
{
public:
  nsHTMLButtonControlFrame();
  ~nsHTMLButtonControlFrame();


  NS_IMETHOD  Destroy(nsPresContext *aPresContext);

  NS_IMETHOD  QueryInterface(const nsIID& aIID, void** aInstancePtr);

  NS_IMETHOD Paint(nsPresContext*      aPresContext,
                   nsIRenderingContext& aRenderingContext,
                   const nsRect&        aDirtyRect,
                   nsFramePaintLayer    aWhichLayer,
                   PRUint32             aFlags = 0);

  NS_IMETHOD Reflow(nsPresContext*          aPresContext,
                    nsHTMLReflowMetrics&     aDesiredSize,
                    const nsHTMLReflowState& aReflowState,
                    nsReflowStatus&          aStatus);

  virtual PRBool IsContainingBlock() const;
  
  NS_IMETHOD HandleEvent(nsPresContext* aPresContext, 
                         nsGUIEvent* aEvent,
                         nsEventStatus* aEventStatus);

  NS_IMETHOD GetFrameForPoint(const nsPoint& aPoint, nsFramePaintLayer aWhichLayer, nsIFrame** aFrame);

  NS_IMETHOD SetInitialChildList(nsPresContext* aPresContext,
                                 nsIAtom*        aListName,
                                 nsIFrame*       aChildList);

  NS_IMETHOD  Init(nsPresContext*  aPresContext,
                   nsIContent*      aContent,
                   nsIFrame*        aParent,
                   nsStyleContext*  aContext,
                   nsIFrame*        asPrevInFlow);

  virtual nsStyleContext* GetAdditionalStyleContext(PRInt32 aIndex) const;
  virtual void SetAdditionalStyleContext(PRInt32 aIndex, 
                                         nsStyleContext* aStyleContext);
 
  NS_IMETHOD AppendFrames(nsIAtom*        aListName,
                          nsIFrame*       aFrameList);

  NS_IMETHOD InsertFrames(nsIAtom*        aListName,
                          nsIFrame*       aPrevFrame,
                          nsIFrame*       aFrameList);

  NS_IMETHOD RemoveFrame(nsIAtom*        aListName,
                         nsIFrame*       aOldFrame);

  NS_IMETHOD ReplaceFrame(nsIAtom*        aListName,
                          nsIFrame*       aOldFrame,
                          nsIFrame*       aNewFrame);

#ifdef ACCESSIBILITY
  NS_IMETHOD GetAccessible(nsIAccessible** aAccessible);
#endif

#ifdef DEBUG
  NS_IMETHOD GetFrameName(nsAString& aResult) const {
    return MakeFrameName(NS_LITERAL_STRING("ButtonControl"), aResult);
  }
#endif

  NS_IMETHOD_(PRInt32) GetFormControlType() const;
  NS_IMETHOD GetName(nsAString* aName);
  NS_IMETHOD GetValue(nsAString* aName);
  NS_IMETHOD OnContentReset();

  void SetFocus(PRBool aOn, PRBool aRepaint);
  void ScrollIntoView(nsPresContext* aPresContext);

  NS_IMETHOD GetFormContent(nsIContent*& aContent) const;
  virtual nscoord GetVerticalInsidePadding(nsPresContext* aPresContext,
                                           float aPixToTwip,
                                           nscoord aInnerHeight) const;
  virtual nscoord GetHorizontalInsidePadding(nsPresContext* aPresContext,
                                             float aPixToTwip, 
                                             nscoord aInnerWidth,
                                             nscoord aCharWidth) const;

  // nsIFormControlFrame
  NS_IMETHOD SetProperty(nsPresContext* aPresContext, nsIAtom* aName, const nsAString& aValue);
  NS_IMETHOD GetProperty(nsIAtom* aName, nsAString& aValue); 
  NS_IMETHOD SetSuggestedSize(nscoord aWidth, nscoord aHeight);

  // Inserted child content gets its frames parented by our child block
  virtual nsIFrame* GetContentInsertionFrame() {
    return GetFirstChild(nsnull)->GetContentInsertionFrame();
  }

protected:
  void ReParentFrameList(nsFrameManager* aFrameManager, nsIFrame* aFrameList);
  virtual PRBool IsReset(PRInt32 type);
  virtual PRBool IsSubmit(PRInt32 type);
  void ReflowButtonContents(nsPresContext* aPresContext,
                            nsHTMLReflowMetrics& aDesiredSize,
                            const nsHTMLReflowState& aReflowState,
                            nsIFrame* aFirstKid,
                            const nsSize& aAvailSize,
                            nsReflowReason aReason,
                            nsMargin aFocusPadding,
                            nsReflowStatus& aStatus);
  NS_IMETHOD AddComputedBorderPaddingToDesiredSize(nsHTMLReflowMetrics& aDesiredSize,
                                                   const nsHTMLReflowState& aSuggestedReflowState);
  NS_IMETHOD_(nsrefcnt) AddRef(void);
  NS_IMETHOD_(nsrefcnt) Release(void);

  PRIntn GetSkipSides() const;
  PRBool mInline;
  nsButtonFrameRenderer mRenderer;

  //Resize Reflow OpitmizationSize;
  nsSize                mCacheSize;
  nscoord               mCachedAscent;
  nscoord               mCachedMaxElementWidth;
};

#endif




