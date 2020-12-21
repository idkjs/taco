module Border = {
  open Emotion;

  type radius = [ `Zero | `Rounded | `Full ];
  type t = [`Zero | `One | `Twoo ];

  let styles = (border) => {
    switch (border) {
      | Some(b) => switch (b) {
        | `Zero => css([unsafe("border", "none")])
        | `One(color) => css([unsafe("border", "1px solid " ++ color)])
        | `Twoo(color) => css([unsafe("border", "2px solid " ++ color)])
        }
      | None => ""
    }
  };

  let stylesWithDirection = (direction, border) => {
    switch (border) {
      | Some(b) => switch (b) {
        | `Zero => css([unsafe("border-" ++ direction, "none")])
        | `One(color) => css([unsafe("border-" ++ direction, "1px solid " ++ color)])
        | `Twoo(color) => css([unsafe("border-" ++ direction, "2px solid " ++ color)])
        }
      | None => ""
    }
  };
};

module Shadow = {
  open Emotion;

  type t = [`Zero | `Small | `Medium | `Large ];

  let styles = (shadow: t) => {
    switch (shadow) {
      | `Zero => css([])
      | `Small => css([unsafe("box-shadow", "0 4px 10px hsla(0, 0%, 0%, 0.05)")])
      | `Medium => css([unsafe("box-shadow", "0 4px 10px hsla(0, 0%, 0%, 0.1)")])
      | `Large => css([unsafe("box-shadow", "0 6px 24px hsla(0, 0%, 0%, 0.1)")])
    };
  };
};

[@react.component]
let make =
    (
      ~inline=false,
      ~padding=0,
      ~height="auto",
      ~width="auto",
      ~background=Colors.white,
      ~backgroundHover=?,
      ~borderRadius=`Rounded,
      ~border=?,
      ~borderTop=?,
      ~borderBottom=?,
      ~borderLeft=?,
      ~borderRight=?,
      ~shadow=`Zero,
      /* Container can have any ReactEvent, TODO: add all events here... */
      ~onClick=?,
      ~onMouseOver=?,
      ~onMouseLeave=?,
      ~children=React.null,
    ) => {
  let className =
    Cn.make([
      [%css "position: relative; flex-shrink: 0;"],
      inline ? [%css "display: inline-block; "] : "",
      Belt.Option.isSome(onClick) ? [%css "cursor: pointer;"] : "",
      [%css "width: $width"],
      [%css "height: $height"],
      [%css "background: $background"],
      switch (backgroundHover) {
        | Some(background) => [%css "&:hover { background: $background; }"]
        | None => ""
      },
      switch (borderRadius) {
        | `Zero => ""
        | `Rounded => [%css "border-radius: 2px"]
        | `Full => [%css "border-radius: 999px"]
      },
      Border.styles(border),
      Border.stylesWithDirection("top", borderTop),
      Border.stylesWithDirection("bottom", borderBottom),
      Border.stylesWithDirection("left", borderLeft),
      Border.stylesWithDirection("right", borderRight),
      Spacer.spaceStyles("padding", padding),
      Shadow.styles(shadow),
    ]);

  <div className ?onClick ?onMouseOver ?onMouseLeave> children </div>;
};
