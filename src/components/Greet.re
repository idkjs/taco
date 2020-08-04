module StyledComponent = [%styled.div
  {|
  display: flex;
  justify-content: center;
  align-items: center;

  height: 100vh;
  width: 100vw;
|}
];

module Text = [%styled.p
  {|
  font-size: 1.875rem;
  color: #1a202c;
  margin-bottom: 1rem;
|}
];

module Link = [%styled.p
  {|
  font-size: 1.875rem;
  color: #4299e1;
  text-decoration: none;
|}
];

module Theme = {
  let unit = 4;
  let unitize = v => v * unit;

  module Colors =
}

module Container = {

  module Shadow = {
    type t = [ | `Default | `Md | `Outline];

    /* let toCSS = shadow => {
      switch (shadow) {
      | Some(`Default) =>
        boxShadow(
          ~x=`zero,
          ~y=`px(2),
          ~blur=`px(4),
          ~spread=`zero,
          ~inset=false,
          defaultColor,
        )
      | Some(`Md) =>
        boxShadow(
          ~x=`zero,
          ~y=`px(8),
          ~blur=`px(16),
          ~spread=`zero,
          ~inset=false,
          mdColor,
        )
      | Some(`Outline) =>
        boxShadow(
          ~x=`zero,
          ~y=`px(0),
          ~blur=`px(0),
          ~spread=`zero,
          ~inset=false,
          outlineColor,
        )
      | None => `Transparent->WL.Color.toEmotion->boxShadow
      };
    }; */
  };

  module Color = {
    type t = string;
  }

  module Border = {
    [@genType]
    type t = [ | `Zero | `One(Color.t) | `Two(Color.t)];
    type radius = [ | `None | `Default | `Full];

    /* let toCSS = (position, border) => {
      switch (border) {
      | `Zero => position(`px(0), `solid, `Transparent->WL.Color.toEmotion)
      | `One(color) => position(`px(1), `solid, color->WL.Color.toEmotion)
      | `Two(color) => position(`px(2), `solid, color->WL.Color.toEmotion)
      };
    };

    [@genType "fromJs"]
    let fromJs = (string, color) => {
      switch (string) {
      | "Zero" => Some(`Zero(color))
      | "One" => Some(`One(color))
      | "Two" => Some(`Two(color))
      | _ => None
      };
    }; */
  };

/*   let styles =
      (
        ~background: WL.Color.t,
        ~backgroundHover: option(WL.Color.t),
        ~shadow=?,
        ~content,
      ) => {
    let backgroundHover =
      switch (backgroundHover, background) {
      | (Some(color), _) => backgroundColor(color->WL.Color.toEmotion)
      | (None, bgColor) => backgroundColor(bgColor->WL.Color.toEmotion)
      };

    css([
      background->WL.Color.toEmotion->backgroundColor,
      content->WL.Color.toEmotion->color,
      hover([backgroundHover]),
      shadow->Shadow.toCSS,
    ]);
  };
 */

  [@react.component]
  let make =
      (
        ~inline=false,
        ~height="auto",
        ~width="auto",
        ~background=`Mono700,
        ~backgroundHover=?,
        ~borderRadius=`None,
        ~color=`Mono200,
        ~shadow=?,
        ~border=?,
        ~borderTop=?,
        ~borderBottom=?,
        ~borderLeft=?,
        ~borderRight=?,

        /* Container can have any ReactEvent */
        ~onClick=?,
        ~onMouseOver=?,
        ~onMouseLeave=?,
        ~children=React.null,
      ) => {
    let className =
      Cn.make([
        [%css "position: relative; flex-shrink: 0;"],
        inline ? [%css "display: inline-block; "]: "",
        Belt.Option.isSome(onClick) ? [%css "cursor: pointer;"] : "",
        [%css "width: $width"],
        [%css "height: $height"],
        switch (borderRadius) {
        | `None => [%css "border-radius: 0"]
        | `Default => [%css "border-radius: 4px"]
        | `Full => [%css "border-radius: 999999px"]
        },
        /* borderStyles(
          ~border?,
          ~borderTop?,
          ~borderRight?,
          ~borderBottom?,
          ~borderLeft?,
          (),
        ),
        styles(~background, ~backgroundHover, ~content=color, ~shadow?), */
      ]);

    <div className ?onClick ?onMouseOver ?onMouseLeave> children </div>
  };
};

module Distribute = {
  type direction = | Horizontal | Vertical;
  type align = | Start | End | Center;
  type distribute =
    | SpaceAround
    | SpaceBetween
    | SpaceEvenly
    | Start
    | Center
    | End;

  [@react.component]
  let make =
      (
        ~gap=0,
        ~align=Start,
        ~distribute=SpaceAround,
        ~direction=Horizontal,
        ~fullHeight=true,
        ~fit as _, /* currnetly not implemented */
        ~children,
      ) => {
    let _gapValue = Theme.unitize(gap);
    let className =
      Cn.make([
        [%css "display: flex;"],
        switch (direction) {
          | Horizontal => [%css "flex-direction: row;"]
          | Vertical => [%css "flex-direction: column;"]
        },
        fullHeight ? [%css "height: 100%"] : "",
        switch (align) {
        | Start => [%css "align-items: flex-start"]
        | Center => [%css "align-items: center"]
        | End => [%css "align-items: flex-end"]
        },
        switch (distribute) {
        | SpaceAround => [%css "justify-content: space-around"]
        | SpaceBetween => [%css "justify-content: space-between"]
        | SpaceEvenly => [%css "justify-content: space-evenly"]
        | Start => [%css "justify-content: flex-start"]
        | Center => [%css "justify-content: center"]
        | End => [%css "justify-content: flex-end"]
        },
        /*
        [%css {|
          & > *:not(:last-child) {
            margin-bottom: $gapValue;
          }
        |}],
        fit ? [%css {|
          & > * {
            flex: 1, 1, 0;
          }
        |}]: [%css {|
          & > * {
            flex: 0, 0, auto;
          }
        |}] */
      ]);

    <div className> children </div>;
  };
}

module Spacer = {
  open Theme;

  [@genType "Spacer"]
  [@react.component]
  let make = (~children=?, ~top=0, ~left=0, ~right=0, ~bottom=0, ~all=0) => {
    let className =
      Cn.make([
        switch (unitize(top), unitize(left), unitize(right), unitize(bottom), unitize(all)) {
        | (value, _, _, _, _) when value != 0 => [%css {j| margin-top: $value; |j}]
        | (_, value, _, _, _) when value != 0 => [%css {j| margin-left: $value; |j}]
        | (_, _, value, _, _) when value != 0 => [%css {j| margin-right: $value; |j}]
        | (_, _, _, value, _) when value != 0 => [%css {j| margin-bottom: $value; |j}]
        | (_, _, _, _, value) when value != 0 => [%css {j| margin: $value; |j}]
        | _ => [%css ""]
        },
      ]);

    <div className>
      {switch (children) {
       | None => React.null
       | Some(c) => c
       }}
    </div>;
  };
};

[@react.component]
let make = (~name) => {
  <Container>
    <Spacer all=10>
      <Text>
        {React.string({j|👋 Welcome $name! You can edit me in |j})}
        <code> {React.string("src/components/Greet.re")} </code>
      </Text>
      <Link href="https://reasonml.github.io/reason-react/">
        {React.string("Learn Reason React")}
      </Link>
    </Spacer>
  </Container>;
};
